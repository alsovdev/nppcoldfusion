<cffunction name="formatPrice" output="true">
		<cfargument name="price"/>		
		<cfif isNumeric(price)><cfreturn numberFormat(price,'.00')/><cfelse><cfreturn "(по запросу)"></cfif>
	</cffunction>	
	<cfset request.formatPrice=formatPrice/>	
 
	<cfquery name="qServiceParamPrice" datasource="#request.DS#">
		select 
		 t.service_param_price_id			
		,t.service_param_id
		,t.pricing_model_id
		,m.pricing_model
		,m.pricing_model_short
		,m.pricing_model_code
		,t.pricing_period
		,t.rating_period
		,t.price
		<!--- ,t.discount_policy_id --->
		,t.dt_from
		,t.dt_to
		,t.status
		,t.descr
		from service_param_price t	
		left outer join pricing_model m on (t.pricing_model_id=m.pricing_model_id)		
		where t.service_param_id=<cfqueryparam cfsqltype="cf_sql_integer" value="#d.service_param_id#"/>
		order by 1
	</cfquery>
	
	<cfoutput>
		<p class="b">
			Цены компонента услуги (без НДС)
		</p>