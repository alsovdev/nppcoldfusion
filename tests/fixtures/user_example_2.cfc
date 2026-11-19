<cfquery name="local.qInstanceOperation" result="local.result">
	select 
	<m:field_set titleMapOut="local.titleMap" lengthOut="local.fieldCount">
		<m:field>o.instance_operation_uid::text as instance_operation_uid</m:field>
		<m:field>o.operation</m:field>
<!--- 		<m:field>o.resource_realm_id</m:field>
		<m:field>r.resource_realm</m:field> --->
		<m:field>o.instance_uid::text as instance_uid</m:field>
		<m:field>to_char(o.dt_submit, 'YYYY-MM-DD"T"HH24:MI:SS.FF3TZHTZM') as dt_submit</m:field>
		<m:field>o.submit_result</m:field>
		<m:field>o.error_log</m:field>
		<m:field>o.note</m:field>
		<m:field>to_char(o.dt_start, 'YYYY-MM-DD"T"HH24:MI:SS.FF3TZHTZM') as dt_start</m:field>
		<m:field>to_char(o.dt_finish, 'YYYY-MM-DD"T"HH24:MI:SS.FF3TZHTZM') as dt_finish</m:field>
		<m:field title="Длит. сек">extract('epoch' from coalesce(o.dt_finish,CURRENT_TIMESTAMP)- o.dt_start) as duration</m:field>
		<m:field formatter=#request.castToBool#>o.is_successful</m:field>
		<m:field>e.display_name</m:field>
		<m:field>e.service_id</m:field>
		<m:field>e.specification_item_id</m:field>
		<m:field>to_char(o.dt_created, 'YYYY-MM-DD"T"HH24:MI:SS.FF3TZHTZM') as dt_created</m:field>	
		<m:field>to_char(o.dt_updated, 'YYYY-MM-DD"T"HH24:MI:SS.FF3TZHTZM') as dt_updated</m:field>	
		<m:field>o.updater_id</m:field>
		<m:field>u.login as updater_login</m:field>
		<m:field>u.shortname as updater_shortname</m:field>
		<m:field>v.svc</m:field>
		<m:field>so.man</m:field>
		<m:field>so.svc_operation_id</m:field>
		<m:field formatter=#request.castToBool#>coalesce((o.dt_start IS NOT NULL AND o.dt_finish IS NULL AND o.submit_result='201'),false) as is_in_progress</m:field>
		<m:field formatter=#request.castToBool#>coalesce((o.dt_start IS NULL AND o.submit_result='201'),false) as is_pending</m:field>
	</m:field_set>	
	from instance_operation o
	join instance e on (o.instance_uid=e.instance_uid)
	join specification_item i on (e.specification_item_id=i.specification_item_id)		
	join specification s on (i.specification_id=s.specification_id)		
	join contract d on (s.contract_id=d.contract_id)		
	join contragent k on (d.contragent_id=k.contragent_id)
	join svc v on (e.service_id=v.svc_id)
	join svc_operation so on (v.svc_id=so.svc_id AND o.operation=so.operation)
	<!--- left outer join resource_realm r on (o.resource_realm_id=r.resource_realm_id) --->	
	left outer join usr u on (o.updater_id=u.usr_id)
	where <!--- u.usr_id=<cfqueryparam cfsqltype="cf_sql_integer" value=#arguments.usrId#/> AND--->
	 o.instance_operation_uid=<cfqueryparam cfsqltype="cf_sql_other" value="#arguments.instanceOperationUid#" null=#!isValid('guid',arguments.instanceOperationUid)#/>
	AND s.specification_id=<cfqueryparam cfsqltype="cf_sql_integer" value=#arguments.specificationId#/>
</cfquery>
