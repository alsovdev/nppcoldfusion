<cfsilent>
<cfimport prefix="m" taglib="lib"/>
<cfimport prefix="c" taglib="lib/controls"/>
<cfimport prefix="d" taglib="lib/data"/>
<cfimport prefix="layout" taglib="layout"/>
</cfsilent>

<!--- этого можно было не делать, ошибка возникала при вычитании нулла в cfm --->
<cffunction name="safeCompareNum" returntype="boolean">
	<cfargument name="n1" type="any"/>
	<cfargument name="operator" type="string"/>
	<cfargument name="n2"  type="any" default=0/>

	<cfif NOT isNumeric(arguments.n1) OR NOT isNumeric(arguments.n2)>
		<cfreturn false/>
	</cfif>
	
	<cfswitch expression=#arguments.operator#>
		<cfcase value="GT">
			<cfreturn (n1 GT n2)/>
		</cfcase>		
		<cfcase value="LT">
			<cfreturn (n1 LT n2)/>
		</cfcase>		
		<cfcase value="EQ,IS">
			<cfreturn (n1 EQ n2)/>
		</cfcase>		
		<cfcase value="NEQ">
			<cfreturn (n1 NEQ n2)/>
		</cfcase>		
		<cfcase value="GE,GTE">
			<cfreturn (n1 GE n2)/>
		</cfcase>			
		<cfcase value="LE,LTE">
			<cfreturn (n1 LE n2)/>
		</cfcase>		
		<cfdefaultcase>
			<cfreturn false/>
		</cfdefaultcase>
	</cfswitch>	
</cffunction>

<cffunction name="safeNumberFormat" returntype="string">
	<cfargument name="num" type="any"/>
	<cfargument name="format" type="string"/>
	
	<cfif NOT isNumeric(arguments.num)>
		<cfreturn ""/>
	</cfif>
	<cftry>
		<cfreturn numberFormat(arguments.num, arguments.format)/>
		<cfcatch type="any">
			<cfreturn ""/>
		</cfcatch>
	</cftry>
</cffunction>

<m:prepare_ls entity="cloud_capacity" settingsKey="cloud_capacity" accessObject="" pageInfoOut="pageInfo" trackOut="tr"/>

<cfquery name="qTS">
	select 
	 (select max(ts) from vmreports.compute) as ts_compute
	,(select max(ts) from vmreports.host) as ts_host
</cfquery>

<!--- по результатам разбора ошибок. 
1. Обрамлять минус пробелами (а то читал gb_provisioned-vm_ram_alloc как одно имя переменной
2. Всю арифметику делать в запросе - SQL работает с нуллами гораздо лучше CFML, в котором они превращаются в пустые строки, провоцируя ошибки --->
<cfquery name="qRead">
with 
<!--- capacity as (
select "Cluster" as cluster, count(*) as hosts, sum(cores) as cores, round(sum(ghz)::numeric,1) as ghz, round(sum(ram)) as ram 
from (
	select "Cluster", "Host"
	, avg("Host_CPU_Cores") as cores, avg("Host_CPU_Cores"*"Host_CPU_Speed") as ghz, avg("Host_RAM"*.85) as ram 
	from vmreports.compute 
	where ts=(select max(ts) from vmreports.compute) 
	group by "Cluster","Host"
	order by "Cluster","Host"
) host 
group by "Cluster"), --->

usage as (
select 
	 c."Cluster" as cluster
	,count(c."UUID_VM") as vms
	,sum(c."VM_vCPU_count") as vm_cores
	,sum(c."VM_vCPU_count"*c."VM_is_ON") as vm_cores_on
	,sum(c."VM_vCPU_count"*c."VDC_CPU_Speed") as vm_ghz
	,sum(c."VM_vCPU_count"*c."VDC_CPU_Speed"*c."VM_is_ON") as vm_ghz_on
	,sum(c."VM_CPU_Reserv_GHz") as vm_ghz_reserved
	,sum(c."VM_vCPU_count"*c."VDC_CPU_Speed"*c."VM_CPU_Reserv_perc"/100) as vm_ghz_reserved_c
	,sum(c."VM_vCPU_count"*c."VDC_CPU_Speed"*(case when c."VM_CPU_Reserv_perc" IS null then 20 when c."VM_CPU_Reserv_perc"<=20 then 20 else c."VM_CPU_Reserv_perc" end)/100) as vm_ghz_promised
	-- promised - зарезервированные ГГц, если включить минимальное согласованное резервирование
	,sum(c."VM_RAM_Allocated"*c."VM_is_ON") as vm_ram_alloc_on
	,sum(c."VM_RAM_Allocated") as vm_ram_alloc
	,sum(c."VM_RAM_Used") as vm_ram_used
	,sum(c."VM_CPU_Used_AVG") as vm_ghz_usage
	,sum(c."VM_is_ON") as vms_on
	,sum(s."Disk_Allocated") as disk_allocated
	,sum(s."Disk_Used") as disk_used

	,sum(CASE WHEN c."Organization_Status"='prod' THEN c."VM_CPU_Used_AVG" ELSE 0 END ) as ghz_used_prod
	,sum(CASE WHEN c."Organization_Status"='prod' THEN c."VM_RAM_Used" ELSE 0 END ) as ram_used_prod
	,sum(CASE WHEN c."Organization_Status"='prod' THEN s."Disk_Used" ELSE 0 END ) as disk_used_prod

from vmreports.compute c
left outer join vmreports.storage s on(c."UUID_VM"=s."VM_UUID")
where c.ts=(select max(ts) from vmreports.compute) 
AND s.ts=(select max(ts) from vmreports.storage) 
group by c."Cluster"),

cluster_stat as (
SELECT 
	 h."Cluster" as cluster
	,h."Cluster_v2" as cluster_v2
	,m.models
	,COUNT(*) as hosts_total
	,COUNT(*)-1 as hosts_ha /*не вполне корректно, хосты разного размера, отказ по-разному влияет*/
	,sum(CASE WHEN "Maintenance"='inMaintenance' THEN 1 ELSE 0 END) as hosts_in_maintenance
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN 1 ELSE 0 END) as hosts_in_service
	,sum("CPU_Cores") as cores 
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPU_Cores" ELSE 0 END) as cores_in_service
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPU_Cores"*"CPU_Speed" ELSE 0 END) as ghz_in_service
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPUtoVM" ELSE 0 END) as ghz_provisioned
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "RAMtoVM" ELSE 0 END) as gb_provisioned
	--,sum("CPU_Used_AVG") as host_ghz_usage
	--,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPU_Used_AVG" ELSE 0 END) as host_ghz_usage
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPU_Used" ELSE 0 END) as host_ghz_usage
	,sum(CASE WHEN "Maintenance"='notInMaintenance' THEN "RAM_Total" ELSE 0 END) as ram_in_service
	,avg(CASE WHEN "Maintenance"='notInMaintenance' THEN "CPU_Speed" ELSE 0 END) as ghz
	,max("CPUtoVM") as ghz_subtract_ha
	,max("RAMtoVM") as gb_subtract_ha
	,sum("RAM_Total")/sum("CPU_Cores") as gb_per_core
	,CASE WHEN sum("CPU_Cores"*"CPU_Speed") > 0 THEN sum("CPU_Used_AVG")/sum("CPU_Cores"*"CPU_Speed")*100 ELSE NULL END as cpu_usage_perc
FROM vmreports.host h 
LEFT OUTER JOIN (
	SELECT hi."Cluster", STRING_AGG(DISTINCT hi."Model" || ' [' || (hi.cnt::text) || '] ',', ') as models 
	FROM (
		SELECT hii."Cluster", hii."Model", count(hii."Model") as cnt 
		FROM vmreports.host hii
		WHERE hii.ts=(SELECT max(ts) FROM vmreports.host)
		GROUP BY hii."Cluster", hii."Model"
	) hi GROUP BY hi."Cluster"
) m ON (h."Cluster"=m."Cluster")
WHERE ts=(SELECT max(ts) FROM vmreports.host)
GROUP BY h."Cluster", h."Cluster_v2", m.models
ORDER BY h."Cluster"
),

cluster_naming (cluster,commercial_name) AS (VALUES 
	 ('cl01-vsan','msk1, Intel Cascade Lake 2,9 ГГц')
	,('msk1-pub01-i29','msk1, Intel Cascade Lake 2,9 ГГц')
	,('cl02','msk1, Intel Cascade Lake 3,1 ГГц')
	,('cl04-vsan','msk1, AMD Milan 2,8 ГГц')
	,('cl05-1c','msk1, AMD Raphael 4,5 ГГц')
	,('cl06-vsan','msk1, Intel Ice Lake 2,8 ГГц')
	,('cl07-vsan','msk1, AMD Genoa 4,0 ГГц')
	,('msk1-pub03-a28','msk1, AMD Milan 2,8 ГГц [2]')
	,('msk1-pub08-a27','msk1, AMD Chagall 2,7 ГГц')
),

vsan as (
SELECT "ClusterNew" as cluster_v2, "Total" as total, "Usable" as usable, "Used" as used, "EffectiveFree" as effective_free
FROM vmreports.vsan_storage
WHERE ts=(SELECT max(ts) FROM vmreports.vsan_storage)
)

select 
<d:field_set titleMapOut="titleMap" lengthOut="fieldCount">
	<d:field title="cluster v1">h.cluster as cluster_v1</d:field>
	<d:field title="cluster v2">h.cluster_v2</d:field>
	<d:field title="Коммерческое название">n.commercial_name</d:field>
	<d:field title="Models">h.models</d:field>
	<d:field title="Hosts total" cfSqlType="CF_SQL_INTEGER">coalesce(h.hosts_total,0) as hosts_total</d:field>
	<d:field title="Hosts HA" cfSqlType="CF_SQL_INTEGER">coalesce(h.hosts_ha,0) as hosts_ha</d:field>
	<d:field title="Hosts in mainte nance" cfSqlType="CF_SQL_INTEGER">coalesce(h.hosts_in_maintenance,0) as hosts_in_maintenance</d:field>
	<d:field title="Hosts in service" cfSqlType="CF_SQL_INTEGER">coalesce(h.hosts_in_service,0) as hosts_in_service</d:field>
	<d:field title="Cores Total" cfSqlType="CF_SQL_INTEGER">coalesce(h.cores,0) as cores</d:field>
	<d:field title="Cores in service" cfSqlType="CF_SQL_INTEGER">coalesce(h.cores_in_service,0) as cores_in_service</d:field>
	<d:field title="GHz in service" cfSqlType="CF_SQL_NUMERIC">coalesce(h.ghz_in_service,0) as ghz_in_service</d:field>
	<d:field title="Host GHz used" cfSqlType="CF_SQL_NUMERIC">coalesce(h.host_ghz_usage,0) as host_ghz_usage</d:field>
	<d:field title="Payload GHz used" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ghz_usage,0) as vm_ghz_usage</d:field>
	<d:field title="CPU freq GHz" cfSqlType="CF_SQL_NUMERIC">coalesce(h.ghz,0) as ghz</d:field>
	<d:field title="RAM GB in service" cfSqlType="CF_SQL_NUMERIC">coalesce(h.ram_in_service,0) as ram_in_service</d:field>
	<d:field title="Host CPU usage %" cfSqlType="CF_SQL_NUMERIC">coalesce(h.cpu_usage_perc,0) as cpu_usage_perc</d:field>
<!--- 	<d:field title="Hosts in use">h.hosts</d:field>  --->
	<d:field title="Cores Total" cfSqlType="CF_SQL_INTEGER">coalesce(h.cores,0) as cores_total</d:field>
<!--- 	<d:field title="GHz Capacity">c.ghz as GHz_Capacity</d:field> --->
	<d:field title="GHz Provisioned" cfSqlType="CF_SQL_NUMERIC">coalesce(h.ghz_provisioned - CASE WHEN hosts_in_maintenance > 0 THEN 0 ELSE h.ghz_subtract_ha END,0) as GHz_Provisioned</d:field><!--- за вычетом согласованных резервов на хосте и на HA --->
	<d:field title="GB Provisioned" cfSqlType="CF_SQL_NUMERIC">coalesce(h.gb_provisioned - CASE WHEN hosts_in_maintenance > 0 THEN 0 ELSE h.gb_subtract_ha END,0) as GB_Provisioned</d:field><!--- за вычетом согласованных резервов на хосте и на HA --->
	<d:field title="Payload GHz reserved" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ghz_reserved,0) as vm_ghz_reserved</d:field>
	<d:field title="GHz обещанные" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ghz_promised,0) as vm_ghz_promised</d:field>
	<d:field title="CPU GHz provision rate %" cfSqlType="CF_SQL_NUMERIC">coalesce(round((u.vm_ghz_promised/h.ghz_provisioned)::numeric,2)*100,0) as GHz_provision_rate</d:field>	
	<d:field title="Payload RAM GB alloc" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ram_alloc,0) as vm_ram_alloc</d:field>
	<d:field title="Payload RAM GB alloc ВКЛ" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ram_alloc_on,0) as vm_ram_alloc_on</d:field>
	<d:field title="Payload RAM GB used" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ram_used,0) as vm_ram_used</d:field>
	<d:field title="RAM alloc %" cfSqlType="CF_SQL_NUMERIC">coalesce(round((u.vm_ram_alloc/h.gb_provisioned)::numeric,2)*100,0) as GB_alloc_perc</d:field>
	<d:field title="RAM usage %" cfSqlType="CF_SQL_NUMERIC">coalesce(round((u.vm_ram_used/h.gb_provisioned)::numeric,2)*100,0) as GB_usage_perc</d:field>
	<d:field title="Пере подписка vCPU" cfSqlType="CF_SQL_NUMERIC">coalesce(round((u.vm_cores/h.cores)::numeric,1),0) as oversubscription</d:field><!--- не только по включенным VM--->
	<d:field title="Payload cores" cfSqlType="CF_SQL_INTEGER">coalesce(u.vm_cores,0) as vm_cores</d:field>
	<d:field title="Payload cores ВКЛ" cfSqlType="CF_SQL_INTEGER">coalesce(u.vm_cores_on,0) as vm_cores_on</d:field>
	<d:field title="VMs" cfSqlType="CF_SQL_INTEGER">coalesce(u.vms,0) as vms</d:field>
	<d:field title="VMs ВКЛ" cfSqlType="CF_SQL_INTEGER">coalesce(u.vms_on,0) as vms_on</d:field>
	<d:field title="Payload CPU Usage %" cfSqlType="CF_SQL_NUMERIC">coalesce(u.vm_ghz_usage/h.ghz_in_service*100,0) as vm_cpu_usage_perc</d:field>
	<d:field title="GB/pCore" cfSqlType="CF_SQL_NUMERIC">coalesce(h.gb_per_core,0) as gb_per_core</d:field>
	
	<d:field title="vSAN Total" cfSqlType="CF_SQL_NUMERIC">coalesce(s.total,0) as total</d:field>
	<d:field title="vSAN Usable" cfSqlType="CF_SQL_NUMERIC">coalesce(s.usable,0) as usable</d:field>
	<d:field title="vSAN Used" cfSqlType="CF_SQL_NUMERIC">coalesce(s.used,0) as used</d:field>
	<d:field title="vSAN Effective Free" cfSqlType="CF_SQL_NUMERIC">coalesce(s.effective_free,0) as effective_free</d:field>
	
	<d:field title="Disk Allocated" cfSqlType="CF_SQL_NUMERIC">coalesce(u.disk_allocated,0) as disk_allocated</d:field>
	<d:field title="Disk Used" cfSqlType="CF_SQL_NUMERIC">coalesce(u.disk_used,0) as disk_used</d:field>
	
	<d:field title="GHz Used Prod" cfSqlType="CF_SQL_NUMERIC">coalesce(u.ghz_used_prod,0) as ghz_used_prod</d:field>
	<d:field title="RAM Used Prod" cfSqlType="CF_SQL_NUMERIC">coalesce(u.ram_used_prod,0) as ram_used_prod</d:field>
	<d:field title="Disk Used Prod" cfSqlType="CF_SQL_NUMERIC">coalesce(u.disk_used_prod,0) as disk_used_prod</d:field>

</d:field_set>
from cluster_stat h
left outer join usage u on (h.cluster=u.cluster)
left outer join cluster_naming n on (h.cluster=n.cluster)
left outer join vsan s on (h.cluster_v2=s.cluster_v2)
where 1=1 <!--- <m:filter_build filter=#pageInfo.settings.filter#/> --->
order by <m:order_build sortArray=#pageInfo.settings.sort.sortArray# fieldCount=#fieldCount#/> 
</cfquery>

<cfif structKeyExists(URL,"debug") OR structKeyExists(FORM,"debug")>
	<cfdump var=#qRead#/>
	<cfflush/>
</cfif>

<cfquery name="qTotal" dbtype="query">
select
	 sum(hosts_total) as hosts_total
	,sum(hosts_ha) as hosts_ha
	,sum(hosts_in_maintenance) as hosts_in_maintenance
	,sum(host_ghz_usage) as host_ghz_usage
	,sum(cores_total) as cores_total
	,sum(cores_in_service) as cores_in_service
	,sum(ghz_in_service) as ghz_in_service
	,sum(ghz_provisioned) as ghz_provisioned
	,sum(ram_in_service) as ram_in_service
	,sum(gb_provisioned) as gb_provisioned
	,sum(cores_in_service) as cores_in_service
	,sum(vm_cores) as vm_cores
	,sum(vm_cores_on) as vm_cores_on
	,sum(vm_ghz_usage) as vm_ghz_usage
	,sum(vm_ghz_reserved) as vm_ghz_reserved
	,sum(vm_ghz_promised) as vm_ghz_promised
	,sum(vm_ram_alloc) as vm_ram_alloc
	,sum(vm_ram_alloc_on) as vm_ram_alloc_on
	,sum(vm_ram_used) as vm_ram_used
	,sum(vms) as vms
	,sum(vms_on) as vms_on
	,sum(cores*ghz)/sum(cores) as ghz <!--- рискованно все же делить --->
	
	,sum(disk_allocated) as disk_allocated
	,sum(disk_used) as disk_used
	,sum(usable) as usable
	
	,sum(ghz_used_prod) as ghz_used_prod
	,sum(ram_used_prod) as ram_used_prod
	,sum(disk_used_prod) as disk_used_prod
	
	
from qRead
</cfquery>

<cfif structKeyExists(URL,"debug") OR structKeyExists(FORM,"debug")>
	<cfdump var=#qTotal#/>
	<cfflush/>
</cfif>

<cfif isDefined("output_xls")>
	<layout:xml qRead=#qRead# titleMap=#titleMap# filename="#pageInfo.entity#.xml"/>
	<cfabort/>
	</cfif><cfif isDefined("output_json")>
	<layout:json qRead=#qRead# titleMap=#titleMap# filename="#pageInfo.entity#.json"/>
	<cfabort/>
	</cfif> 
<layout:page section="header" pageInfo=#pageInfo#>		
	<layout:attribute name="title">
		<cfoutput><b>Cloud Capacity</b></cfoutput>
	</layout:attribute>	
	<layout:attribute name="controls"><!--- empty to remove controls (filter link) ---></layout:attribute>	
</layout:page>

<cfoutput query="qTS">
<h3 style="display:inline-block; margin-right:2em;">Актуальность данных</h3>
<b>VM:</b> <span <cfif dateDiff("h",ts_compute,Now()) GT 24> class="err"</cfif>>#dateFormat(ts_compute,"YYYY-MM-DD")# #timeFormat(ts_compute,"HH:MM")#</span>
<b>Хосты:</b> <span <cfif dateDiff("h",ts_host,Now()) GT 24> class="err"</cfif>>#dateFormat(ts_host,"YYYY-MM-DD")# #timeFormat(ts_host,"HH:MM")#</span>
</cfoutput>

<h3>Свободно</h3>

<table class="worktable">	
	<!--- <thead> --->	
		<layout:grid_head titleMap=#titleMap# sortArray=#pageInfo.settings.sort.sortArray#>	
		<!--- <tr> --->		
			<th width="5%" rowspan="2"><layout:column_head name="cluster_v1"/></th>		                 
			<th width="5%" rowspan="2"><layout:column_head name="cluster_v2"/></th>		
			<th width="10%" rowspan="2"><layout:column_head name="commercial_name"/></th> 
			<th width="3%" rowspan="2"><layout:column_head name="hosts_total"/></th> 
			
			<th colspan="7">Свободно</th>
			
			<th width="3%" rowspan="2">ВМ размещено</th>
		
		<!--- </tr> --->
		</layout:grid_head>
		<tr>
			<th width="5%">RAM GB by alloc</th> 
			<th width="5%">RAM GB by usage</th>
			<th width="5%">CPU GHz (текущий резерв)</th>  
			<th width="5%">Ядра 20% (текущий резерв)</th> 
			<th width="5%">Ядра 50% (текущий резерв)</th> 
			<th width="5%">Ядра 80% (текущий резерв)</th>			
			<th width="5%">vSAN GB (alloc)</th>					
		</tr>
	<!--- </thead> --->
	<!--- <tbody>	 --->
	<cfoutput query="qRead">
		<tr>
            <td>#cluster_v1#</td>		                 
			<td>#cluster_v2#</td> 
			<td style="font-size:130%">#commercial_name#</td>                    
  
			<!--- <td class="r" style="font-size:120%">#numberFormat(ghz,".0")#</td>    --->                   
			<td class="r" style="font-size:110%;">#hosts_total#</td>  
            
			<td class="r<cfif safeCompareNum(gb_provisioned - vm_ram_alloc, "LE", 0)> err</cfif>" style="font-size:130%">
			#safeNumberFormat(gb_provisioned-vm_ram_alloc,"0")#</td>	
			<td class="r<cfif safeCompareNum(gb_provisioned - vm_ram_used, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat(gb_provisioned - vm_ram_used,"0")#</td>	
			
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_reserved, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat(ghz_provisioned-vm_ghz_reserved,".0")#</td>	
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_reserved, "LE", 0)> err</cfif>" style="font-size:130%"><cfif ghz GT 0>#safeNumberFormat((ghz_provisioned-vm_ghz_reserved)/ghz/0.2,"0")#</cfif></td>
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_reserved, "LE", 0)> err</cfif>" style="font-size:130%"><cfif ghz GT 0>#safeNumberFormat((ghz_provisioned-vm_ghz_reserved)/ghz/0.5,"0")#</cfif></td>
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_reserved, "LE", 0)> err</cfif>" style="font-size:130%"><cfif ghz GT 0>#safeNumberFormat((ghz_provisioned-vm_ghz_reserved)/ghz/0.8,"0")#</cfif></td>
			
			<td class="r" style="font-size:130%">#safeNumberFormat(effective_free,"0")#</td> 
			
		<!--- 	<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_promised, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat(ghz_provisioned-vm_ghz_promised,".0")#</td>
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_promised, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat((ghz_provisioned-vm_ghz_promised)/ghz/0.2,"0")#</td>
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_promised, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat((ghz_provisioned-vm_ghz_promised)/ghz/0.5,"0")#</td>
			<td class="r<cfif safeCompareNum(ghz_provisioned - vm_ghz_promised, "LE", 0)> err</cfif>" style="font-size:130%">#safeNumberFormat((ghz_provisioned-vm_ghz_promised)/ghz/0.8,"0")#</td>			 --->
			<td class="r">#vms#</td>	
			
		</tr>
	</cfoutput>
	<!--- </tbody> --->
</table>
<!--- <i>Жесткий резерв - если включим минимальное резервирование 20%</i><br/>
<i>Доступная память указана по выделенному объему (используется меньше, доступно больше)</i><br/> --->
<i>Емкость HA вычитается из Capacity, если нет хостов в Maintenance, в противном случае вычитается ресурс хостов в Maintenance. За объем для HA принимается размер наибольшего хоста в кластере по каждому ресурсу (поэтому при выводе в Maintenance маленького хоста расчетная емкость может временно увеличиться, но это только если хосты в кластере разные. Понятнее будет, если мы как резерв будем брать максимальное значение из наибольшего хоста и суммы выведенных в Maintenance хостов)</i>

<h3>Использование подробно</h3>

<layout:grid_summary
	recordCount=#qRead.recordCount#
	footerOut="gridFooter"	
	excelLink="Yes"
	jsonLink="Yes"
/>

 <table class="worktable">	
	<thead>
		<layout:grid_head titleMap=#titleMap# sortArray=#pageInfo.settings.sort.sortArray#>			
			<th width="5%"><layout:column_head name="cluster_v1"/></th>		                 
			<th width="5%"><layout:column_head name="cluster_v2"/></th>                      
			<th width="7%"><layout:column_head name="commercial_name"/></th>                      
			<th width="15%"><layout:column_head name="models"/></th>   	
			<th width="3%"><layout:column_head name="ghz"/></th>                       
			<th width="3%"><layout:column_head name="hosts_total"/></th>                     
			<th width="3%"><layout:column_head name="hosts_ha"/></th>                     
			<th width="3%"><layout:column_head name="hosts_in_maintenance"/></th>	 
<!--- 			<th width="3%"><layout:column_head name="hosts_in_service"/></th>
			<th width="3%"><layout:column_head name="ram_in_service"/></th>	
			<th width="3%"><layout:column_head name="cores_in_service"/></th>	             
			<th width="3%"><layout:column_head name="ghz_in_service"/></th>	 --->
			<th width="3%"><layout:column_head name="host_ghz_usage"/></th>                 
			<th width="3%"><layout:column_head name="vm_ghz_usage"/></th>
			<th width="3%"><layout:column_head name="cpu_usage_perc"/></th>	
			<th width="3%"><layout:column_head name="vm_cpu_usage_perc"/></th>	
			<th width="3%"><layout:column_head name="oversubscription"/></th>	
			<th width="3%"><layout:column_head name="cores_total"/></th>	                 
			<th width="3%"><layout:column_head name="ghz_provisioned"/></th>			         
			<th width="3%"><layout:column_head name="vm_ghz_reserved"/></th>		         
			<th width="3%"><layout:column_head name="vm_ghz_promised"/></th>	
			<th width="3%"><layout:column_head name="vm_cores"/></th>	
			<th width="3%"><layout:column_head name="GHz_provision_rate"/></th>	
			<th width="3%"><layout:column_head name="gb_provisioned"/></th>	
			<th width="3%"><layout:column_head name="vm_ram_alloc"/></th>	
			<th width="3%"><layout:column_head name="vm_ram_used"/></th>	
			<th width="3%"><layout:column_head name="GB_alloc_perc"/></th>	
			<th width="3%"><layout:column_head name="GB_usage_perc"/></th>	
			<th width="3%">ВМ шт.</th>	
			<th width="10%">Средняя ВМ</th>	
		</layout:grid_head>
	</thead>
		
	<cfoutput query="qRead">
		<tr>
			<td>#cluster_v1#</td>		                 
			<td>#cluster_v2#</td>                      
			<td>#commercial_name#</td>                      
			<td>#models#</td>    
			<td class="r">#numberFormat(ghz,".0")#</td>                      
			<td class="r" style="font-size:110%;">#hosts_total#</td>                     
			<td class="r">#hosts_ha#</td>                     
			<td class="r"><cfif hosts_in_maintenance NEQ 0>#hosts_in_maintenance#</cfif></td>			<!--- style="background:lightcoral" ---> 
			<!--- <td class="r">#hosts_in_service#</td>
			<td class="r">#numberFormat(ram_in_service,"0")#</td>		       
			<td class="r">#cores_in_service#</td>	                   
			<td class="r">#numberFormat(ghz_in_service,".0")#</td>	 --->                 
			<td class="r">#numberFormat(host_ghz_usage,".0")#</td>	           
			<td class="r">#numberFormat(vm_ghz_usage,".0")#</td>  						                
			<td class="c" style="font-size:130%;">#numberFormat(cpu_usage_perc,"0")#</td>	
			<td class="c" style="font-size:130%;">#numberFormat(vm_cpu_usage_perc,"0")#</td>	
			<td class="r">#oversubscription#</td>	           
			<td class="r">#cores_total#</td>	                 
			<td class="r">#numberFormat(ghz_provisioned,".0")#</td>			         
			<td class="r">#numberFormat(vm_ghz_reserved,".0")#</td>		         
			<td class="r">#numberFormat(vm_ghz_promised,".0")#</td>	
			<td class="r">#vm_cores#</td>	
			<td class="r">#numberFormat(GHz_provision_rate,"0")#</td>	
			<td class="r">#numberFormat(gb_provisioned,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_alloc,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_used,"0")#</td>	
			<td class="r">#numberFormat(GB_alloc_perc,"0")#</td>	
			<td class="r">#numberFormat(GB_usage_perc,"0")#</td>	
			<td class="r">#vms#</td>	
			<td class="r"><!--- <cftry>
			#numberFormat(vm_cores/vms,".0")#&nbsp;core 
			#numberFormat(vm_ghz_usage/vms_on,".0")#&nbsp;GHz 
			#numberFormat(vm_ghz_usage/vm_cores_on/ghz*100,"0")#% 
			#numberFormat(vm_ram_alloc/vms,".0")#(#numberFormat(vm_ram_used/vms_on,".0")#)&nbsp;GB 
			#numberFormat(disk_allocated/vms,".0")#(#numberFormat(disk_used/vms,".0")#)&nbsp;GB
			<cfcatch><cfdump var=#cfcatch#></cfcatch></cftry></td>	 --->
				<cftry>
					<cfif vms NEQ 0>#numberFormat(vm_cores/vms,".0")#<cfelse> ? </cfif> &nbsp;core
				<cfcatch type="any"></cfcatch></cftry>
				<cftry>
					<cfif vms_on NEQ 0>#numberFormat(vm_ghz_usage/vms_on,".0")#<cfelse> ? </cfif>&nbsp;GHz
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vm_cores_on NEQ 0 AND ghz NEQ 0>#numberFormat(vm_ghz_usage/vm_cores_on/ghz*100,"0")#<cfelse> ? </cfif>%
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vms NEQ 0>#numberFormat(vm_ram_alloc/vms,".0")#<cfelse> ? </cfif>(<cfif vms_on NEQ 0>#numberFormat(vm_ram_used/vms_on,".0")#<cfelse>?</cfif>)&nbsp;GB
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vms NEQ 0>#numberFormat(disk_allocated/vms,".0")#(#numberFormat(disk_used/vms,".0")#)<cfelse> ? </cfif>&nbsp;GB				
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
			</td>
		</tr>
	</cfoutput>
	
	<cfoutput query="qTotal">
		<tr class="b">
			<td colspan="4" class="r b"> Итого</td>
			<td class="r">#numberFormat(ghz,".0")#</td>			                                        
			<td class="r">#hosts_total#</td>                     
			<td class="r">#hosts_ha#</td>  
			<td class="r">#hosts_in_maintenance#</td>	         
<!--- 			<td class="r"></td>	
			<td class="r">#numberFormat(ram_in_service,"0")#</td>	         
			<td class="r">#cores_in_service#</td>	             
			<td class="r">#numberFormat(ghz_in_service,".0")#</td> --->	                 
			<td class="r">#numberFormat(host_ghz_usage,".0")#</td>	
			<td class="r">#numberFormat(vm_ghz_usage,".0")#</td>		     
			<td class="c" style="font-size:130%;">
				<!--- <cftry>#numberFormat(vm_ghz_usage*100/ghz_in_service,"0")#<cfcatch type="any"></cfcatch></cftry> --->
			</td>	
			<td class="r"><cftry>#numberFormat(vm_ghz_usage*100/ghz_in_service,"0")#<cfcatch type="any"></cfcatch></cftry></td>	
			<td class="r" style="font-size:130%;"><cfif cores_in_service NEQ 0>#numberFormat(vm_cores/cores_in_service,".0")#</cfif></td>
			<td class="r">#numberFormat(cores_total,"0")#</td>	                 
			<td class="r">#numberFormat(ghz_provisioned,".0")#</td>			         
			<td class="r">#numberFormat(vm_ghz_reserved,".0")#</td>		         
			<td class="r">#numberFormat(vm_ghz_promised,".0")#</td>	
			<td class="r">#vm_cores#</td>	
			<td class="r"></td>	
			<td class="r">#numberFormat(gb_provisioned,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_alloc,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_used,"0")#</td>	
			<td class="r" style="font-size:130%;"><cfif ram_in_service NEQ 0>#numberFormat(vm_ram_alloc/ram_in_service*100,"0")#</cfif></td>	
			<td class="r" style="font-size:130%;"><cfif ram_in_service NEQ 0>#numberFormat(vm_ram_used/ram_in_service*100,"0")#</cfif></td>	
			<td class="r">#vms#</td>
			<td class="r">
				<cftry>
					<cfif vms NEQ 0>#numberFormat(vm_cores/vms,".0")#<cfelse> ? </cfif> &nbsp;core
				<cfcatch type="any"></cfcatch></cftry>
				<cftry>
					<cfif vms_on NEQ 0>#numberFormat(vm_ghz_usage/vms_on,".0")#<cfelse> ? </cfif>&nbsp;GHz
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vm_cores_on NEQ 0 AND ghz NEQ 0>#numberFormat(vm_ghz_usage/vm_cores_on/ghz*100,"0")#<cfelse> ? </cfif>%
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vms NEQ 0>#numberFormat(vm_ram_alloc/vms,".0")#<cfelse> ? </cfif>(<cfif vms_on NEQ 0>#numberFormat(vm_ram_used/vms_on,".0")#<cfelse>?</cfif>)&nbsp;GB
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
				<cftry>
					<cfif vms NEQ 0>#numberFormat(disk_allocated/vms,".0")#(#numberFormat(disk_used/vms,".0")#)<cfelse> ? </cfif>&nbsp;GB				
				<cfcatch type="any"><cfdump var=#cfcatch#></cfcatch></cftry>
			</td>
		</tr>
	</cfoutput>

</table> 
<!--- <cfdump var=#qTotal#/> --->
<i>Пока выводим избыточный набор колонок для контроля. Кроме того, еще не выбрали, какие колонки удобнее и релевантнее</i>
<br/>
<i>* CPU GHz provision rate % - отношение зарезервированной частоты (с учетом 20% резерва по умолчанию) к наличной частоте процессоров (считая выключенные ВМ - поэтому "мертвые" ВМ искажают статистику, кроме того, что занимают диск)</i>
<br/>
<i>* Для средней ВМ указана аллоцированная память, в скобках - используемая, далее аллоцированное дисковое пространство, в скобках используемое. Диск считается без разделения по политикам (2do). ГГц на ВМ, процент загрузки ядер (** проверить), используемая память - считается по включенным ВМ. Количество ядер, аллоцированная память и диск - по всем ВМ</i>
<br/>
<!--- <cfchart 
    format="png" 
    chartWidth="500" 
    chartHeight="300" 
    seriesplacement="stacked" 
    title="Population Distribution: Males vs Females"
    scalefrom="-100" 
    scaleto="100"
	labelformat="number">

    <!--- Left Side: Males (Negative Values) --->
    <cfchartseries type="bar" seriesLabel="Males" seriesColor="##3366CC">
        <cfchartdata item="Age 0-10" value="-85">
        <cfchartdata item="Age 11-20" value="-70">
        <cfchartdata item="Age 21-30" value="-55">
    </cfchartseries>

    <!--- Right Side: Females (Positive Values) --->
    <cfchartseries type="bar" seriesLabel="Females" seriesColor="##FF99CC">
        <cfchartdata item="Age 0-10" value="82">
        <cfchartdata item="Age 11-20" value="75">
        <cfchartdata item="Age 21-30" value="60">
    </cfchartseries>
</cfchart> --->


<h3>Техническая утилизация</h3>
<layout:grid_summary
	recordCount=#qRead.recordCount#
	footerOut="gridFooter"	
	excelLink="Yes"
	jsonLink="Yes"
/>

<table class="worktable">	
	<thead>	
		
		<layout:grid_head titleMap=#titleMap# sortArray=#pageInfo.settings.sort.sortArray#>	
			<th width="5%"><layout:column_head name="cluster_v1"/></th>		                 
			<th width="5%"><layout:column_head name="cluster_v2"/></th>		
			<th width="10%"><layout:column_head name="commercial_name"/></th> 
			
			<th width="3%"><layout:column_head name="hosts_total"/></th> 
			<th width="3%"><layout:column_head name="ghz"/></th>    
			<th width="3%"><layout:column_head name="gb_per_core"/></th>    
			<th width="3%"><layout:column_head name="vms"/></th>    
			<th width="3%"><layout:column_head name="vms_on"/></th>  

			
			<th width="3%"><layout:column_head name="cpu_usage_perc"/></th>	
			<th width="3%"><layout:column_head name="vm_cpu_usage_perc"/></th>	
			<th width="3%"><layout:column_head name="oversubscription"/></th>	
			<th width="3%"><layout:column_head name="cores_total"/></th>	                 
			<th width="3%"><layout:column_head name="cores_in_service"/></th>	                 
			<th width="3%"><layout:column_head name="ghz_in_service"/></th>	                 
			<th width="3%"><layout:column_head name="ghz_provisioned"/></th>			         
			<th width="3%"><layout:column_head name="vm_ghz_reserved"/></th>
			<th width="3%"><layout:column_head name="vm_ghz_usage"/></th>		         
			<th width="3%"><layout:column_head name="vm_cores"/></th>		 
			<th width="3%"><layout:column_head name="vm_cores_on"/></th>		 
			
			
			<th width="3%"><layout:column_head name="gb_provisioned"/></th>	
			<th width="3%"><layout:column_head name="vm_ram_alloc"/></th>	
			<th width="3%"><layout:column_head name="vm_ram_alloc_on"/></th>	
			<th width="3%"><layout:column_head name="vm_ram_used"/></th>	
			<th width="3%">RAM allloc %</th>	
			<th width="3%">RAM allloc ВКЛ %</th>	
			<th width="3%"><layout:column_head name="GB_usage_perc"/></th>	
			<th width="3%">Емкость vSAN GB</th>	
			<th width="3%">Свободно vSAN % alloc</th>	
			<th width="3%">Свободно vSAN % used</th>
			
			<th width="3%"><layout:column_head name="ghz_used_prod"/></th>
			<th width="3%"><layout:column_head name="ram_used_prod"/></th>
			<th width="3%"><layout:column_head name="disk_used_prod"/></th>
		</layout:grid_head>	
	</thead>
		
	<cfoutput query="qRead">
		<tr>
            <td>#cluster_v1#</td>		                 
			<td>#cluster_v2#</td> 
			<td style="font-size:130%">#commercial_name#</td> 
			
			<td class="r" style="font-size:110%;">#hosts_total#</td>
			<td class="r" style="font-size:120%">#numberFormat(ghz,".0")#</td>                  
			<td class="r" style="font-size:120%">#numberFormat(gb_per_core,".0")#</td>                  
			<td class="r" style="font-size:120%">#numberFormat(vms,"0")#</td>                  
			<td class="r" style="font-size:120%">#numberFormat(vms_on,"0")#</td> 
			  						                
			<td class="c" style="font-size:130%;">#numberFormat(cpu_usage_perc,"0")#</td>	
			<td class="c" style="font-size:130%;">#numberFormat(vm_cpu_usage_perc,"0")#</td>	
			<td class="r">#oversubscription#</td>	           
			<td class="r">#cores_total#</td>	                 
			<td class="r">#cores_in_service#</td>	                 
			<td class="r">#safeNumberFormat(ghz_in_service,".0")#</td>	                 
			<td class="r">#numberFormat(ghz_provisioned,".0")#</td>
			<td class="r">#numberFormat(vm_ghz_reserved,".0")#</td>	
			<td class="r">#numberFormat(vm_ghz_usage,".0")#</td>
			<td class="r">#vm_cores#</td>	
			<td class="r">#vm_cores_on#</td>				

			<td class="r">#numberFormat(gb_provisioned,"0")#</td>
			<td class="r">#numberFormat(vm_ram_alloc,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_alloc_on,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_used,"0")#</td>	
			<!--- <td class="c" style="font-size:130%;"><cfif ram_in_service NEQ 0>#numberFormat(vm_ram_alloc/ram_in_service*100,"0")#</cfif></td>	 --->
			<td class="c" style="font-size:130%;">#numberFormat(GB_alloc_perc,"0")#</td>	
			<td class="c" style="font-size:130%;"><cfif gb_provisioned NEQ 0>#numberFormat(vm_ram_alloc_on/gb_provisioned*100,"0")#</cfif></td>	
			<td class="c" style="font-size:130%;"><cfif gb_provisioned NEQ 0>#numberFormat(vm_ram_used/gb_provisioned*100,"0")#</cfif></td>		
			<td class="c" style="font-size:130%;">#safeNumberFormat(usable,"0")#</td>		
			<td class="c" style="font-size:130%;">
				<cfif usable GT 0>
					<cftry>
						#numberFormat(effective_free/usable*100,"0")#
						<cfcatch type="any"></cfcatch>
					</cftry>
				</cfif>
			</td>	
			<td class="c" style="font-size:130%;">
				<cfif usable GT 0>
					<cftry>
						#numberFormat((usable-used)/usable*100,"0")#
						<cfcatch type="any"></cfcatch>
					</cftry>
				</cfif>
			</td>	
			<td class="c">#safeNumberFormat(ghz_used_prod,".0")#</td>
			<td class="c">#safeNumberFormat(ram_used_prod,"0")#</td>
			<td class="c">#safeNumberFormat(disk_used_prod,"0")#</td>
		</tr>
	</cfoutput>
	
	<cfoutput query="qTotal">
		<tr class="b">
			<td colspan="3" class="r b"> Итого</td>
						                                        
			<td class="r">#hosts_total#</td>
			<td class="r" style="font-size:120%">#numberFormat(ghz,".0")#</td>                  
			<td class="r" style="font-size:120%"></td>                  
			<td class="r" style="font-size:120%">#numberFormat(vms,"0")#</td>                  
			<td class="r" style="font-size:120%">#numberFormat(vms_on,"0")#</td> 
			  						                
			<td class="c" style="font-size:130%;"></td>	
			<td class="c" style="font-size:130%;"></td>	
			<td class="r"></td>	           
			<td class="r">#cores_total#</td>	                 
			<td class="r">#cores_in_service#</td>	                 
			<td class="r">#safeNumberFormat(ghz_in_service,".0")#</td>	                 
			<td class="r">#numberFormat(ghz_provisioned,".0")#</td>
			<td class="r">#numberFormat(vm_ghz_reserved,".0")#</td>	
			<td class="r">#numberFormat(vm_ghz_usage,".0")#</td>
			<td class="r">#vm_cores#</td>	
			<td class="r">#vm_cores_on#</td>				

			<td class="r">#numberFormat(gb_provisioned,"0")#</td>
			<td class="r">#numberFormat(vm_ram_alloc,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_alloc_on,"0")#</td>	
			<td class="r">#numberFormat(vm_ram_used,"0")#</td>	
			<td class="c" style="font-size:130%;"></td>	
			<td class="c" style="font-size:130%;"></td>	
			<td class="c" style="font-size:130%;"></td>		
			<td class="c" style="font-size:130%;">#safeNumberFormat(usable,"0")#</td>
			<td class="c" style="font-size:130%;">
				<cfif usable GT 0>
					<cftry>
						#numberFormat(effective_free/usable*100,"0")#
						<cfcatch type="any"></cfcatch>
					</cftry>
				</cfif>
			</td>	
			<td class="c" style="font-size:130%;">
				<cfif usable GT 0>
					<cftry>
						#numberFormat((usable-used)/usable*100,"0")#
						<cfcatch type="any"></cfcatch>
					</cftry>
				</cfif>
			</td>	
			<td class="c">#safeNumberFormat(ghz_used_prod,".0")#</td>
			<td class="c">#safeNumberFormat(ram_used_prod,"0")#</td>
			<td class="c">#safeNumberFormat(disk_used_prod,"0")#</td>
		</tr>
	</cfoutput>
</table>

<i>*** Добавить дневные и недельные максимумы. Возможно, со сглаживанием и персентилем</i>
<br/>

<cfdump var=#this.datasources[request.ds].connectionString#/>

<layout:page section="footer"/>

