<?
require_once('../inc/email.inc');
require_once('../inc/profile.inc');

function get_position($credit){
	if(isset($credit)){
	$result = mysql_query("select count(*) from user where total_credit > $credit");
	$row = mysql_fetch_array($result);
	return $row[0];
	}
	else{
	 echo " ";
	}
}
function get_position_rac($expavg_credit){
	if(isset($expavg_credit)){
	$result = mysql_query("select count(*) from user where expavg_credit > $expavg_credit");
	$row = mysql_fetch_array($result);
	return $row[0];
	}
	else{
	 echo " ";
	}
}
?>


