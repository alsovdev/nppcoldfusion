<cfquery name="local.qCfsParam">
	WITH RECURSIVE r AS (			
		SELECT
		1 AS i
		,e.display_name
		,s.svc
		,sop.svc_operation_cfs_param as param
		,p.param_value::text
		,o.instance_uid::text
		FROM instance e
		JOIN instance_operation o ON (e.instance_uid=o.instance_uid AND o.operation='create')
		JOIN instance_operation_cfs_param p on (o.instance_operation_uid=p.instance_operation_uid)
		JOIN svc s on (e.service_id=s.svc_id)
		--JOIN instance_operation_cfs_param op on (p.instance_operation_cfs_param_uid=op.instance_operation_cfs_param_uid)
		JOIN svc_operation_cfs_param sop on (p.svc_operation_cfs_param_id=sop.svc_operation_cfs_param_id AND sop.ref_svc_id > 0 AND sop.is_actual)
		--LEFT JOIN instance_cfs_param rp on (e.instance_uid=rp.instance_uid )
		--LEFT JOIN instance ri on (rp.instance_uid=ri.instance_uid)
		WHERE e.instance_uid=<cfqueryparam cfsqltype="cf_sql_other" value=#local.instance_uid# null=#!isValid('guid',local.instance_uid)#/>

		UNION

		SELECT
		i+1 AS i
		,e.display_name
		,s.svc
		,p.param
		,p.param_value
		,p.instance_uid::text
		FROM instance_cfs_param p
		JOIN instance e on (p.instance_uid=e.instance_uid)
		JOIN svc s on (e.service_id=s.svc_id)
		JOIN r on (r.param_value=p.instance_uid::text)
		WHERE r.i < 10
	)
	select param, param_value from r
	order by r.i desc
</cfquery>
