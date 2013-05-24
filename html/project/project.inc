<?php

// This is a sample project file.
// Modify it to suit your project.
// Put your version in html/project/project.inc
// add tra() around visible strings to make them translatable
// see inc/translation.inc and http://boinc.berkeley.edu/trac/wiki/TranslateProject for Details

require_once("../inc/util.inc");

$master_url = parse_config(get_config(), "<master_url>");
define("PROJECT", "REPLACE WITH PROJECT NAME");
define("URL_BASE", $master_url);
define("IMAGE_PATH", "../user_profile/images/");
define("IMAGE_URL", "user_profile/images/");
define("PROFILE_PATH", "../user_profile/");
define("PROFILE_URL", "user_profile/");
define("LANGUAGE_FILE", "languages.txt");
define("STYLESHEET", "white.css");
//define("STYLESHEET2", "xxx.css");
define("FORUM_QA_MERGED_MODE", false); // Set to true to merge Message boards and Q&A section
define("COPYRIGHT_HOLDER", "REPLACE WITH COPYRIGHT HOLDER");
define("SYS_ADMIN_EMAIL", "admin@$master_url");
define("UOTD_ADMIN_EMAIL", "admin@$master_url");
    // who gets user of the day pool running low e-mails?
//define("MEMCACHE_SERVERS", "127.0.0.1:11211");

// Email addresses separated by pipe ( | ) that will receive user reported 
// offensive forum posts.
define("POST_REPORT_EMAILS", "moderator1@$master_url|moderator2@$master_url");

function project_banner($title, $prefix) {
    // Put your project title and logo here
    // If you include any links, prepend URL with $prefix

    echo "<div class=\"page_title\">$title</div>";
}

function project_footer($show_return, $show_date, $prefix) {
    // If you include any links, prepend URL with $prefix
    echo "<br><hr noshade size=1><center>";
    if ($show_return) {
        echo "<a href=".$prefix."index.php>".tra("Main page")."</a> &middot; <a href=".$prefix."home.php>".tra("Your account")."</a> &middot; <a href=".$prefix."forum_index.php>".tra("Message boards")."</a><br>\n";
    }
    echo "<br><br>".tra("Copyright")." &copy; ".gmdate("Y ").COPYRIGHT_HOLDER."</center>\n";
    if ($show_date) {
        $t = time_str(time());
        echo "<span class=\"note\">".tra("Generated")." $t</span>\n";
    }
}

// Authorize access to administrative pages.
// You can check for login, IP address, or whatever you want.
//
function auth_ops_example() {
    // if running from cmdline, skip checks
    //
    if (!$_SERVER['REMOTE_ADDR']) {
        return;
    }

    // example: require login as a particular user (id 1 in this case)
    //
    if (0) {
        auth_ops_userid(array(1));
        return;
    }

    // example: require that logged-in user have ADMIN or DEV flags
    // set in their forum_prefs.privilege
    //
    if (0) {
        auth_ops_privilege();
        return;
    }
}

function show_profile_heading1() {
    return tra("Your personal background.");
}

function show_profile_question1() {
    return tra("Tell us about yourself. You could tell us where you're from, your age, occupation, hobbies, or anything else about yourself.");
}

function show_profile_heading2() {
    return tra("Your opinions about %1", PROJECT);
}

function show_profile_question2() {
    return tra("Tell us your thoughts about %1<ol>
    <li>Why do you run %1?
    <li>What are your views about the project?
    <li>Any suggestions?
    </ol>", PROJECT);
}

function project_workunit($wu){
    // shown in the workunit page
}

function project_user_summary($user){
    // shown in the user summary page
}

function project_user_page_private($user){
    // shown in the private account page
}

function project_user_credit($user){
    // shown in the the private account page, credit area
}

function project_forum_post_rules() {
    // additional forum post rules
    return "";
}

function page_head(
    $title, $java_onload=null, $title_plain=null, $prefix="", $head_extra=null
) {
    global $caching, $cache_control_extra, $did_page_head;

    $stylesheet = URL_BASE.STYLESHEET;
    $rssname = PROJECT . " RSS 2.0";
    $rsslink = URL_BASE."rss_main.php";
    if (!$caching) {
        header("Content-type: text/html; charset=utf-8");
        header ("Expires: Mon, 26 Jul 1997 05:00:00 UTC");    // Date in the past
        header ("Last-Modified: " . gmdate("D, d M Y H:i:s") . " UTC"); // always modified
        header ("Cache-Control: $cache_control_extra no-cache, must-revalidate, post-check=0, pre-check=0");  // HTTP/1.1
        header ("Pragma: no-cache");                          // HTTP/1.0
    }
		?>

    <!DOCTYPE HTML>
    <html><head>
		<?
    if ($head_extra) {
        echo "\n$head_extra\n";
    }
    if (!$title_plain) {
        echo "<title>".sanitize_tags($title)."</title>\n";
    } else {
        echo "<title>".sanitize_tags($title_plain)."</title>\n";
    }
		?>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">          
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<?
		include ('schedulers.txt');
		?>
		<!-- Bootstrap -->
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link href="./bootstrap/css/bootstrap.min.css" rel="stylesheet" media="screen">
		<link href="./bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
		<!-- to override default bootstrap -->
		<link href="./style.css" rel="stylesheet" media="screen">             
		<script src="./bootstrap/js/jquery-2.0.0.min.js"></script>
		<script src="./bootstrap/js/bootstrap.min.js"></script>                                     
		<script src="bbcode_toolbar.js"></script>
		</head>
		<body>
		<div class="navbar ">
			<div class="navbar-inner">
			<div class="container">
			<!-- .btn-navbar is used as the toggle for collapsed navbar content -->
				<a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
				</a>
				<!-- Be sure to leave the brand out there if you want it shown -->
				<a class="brand" href="index.php"><?echo PROJECT?></a>
					<ul class="nav">
						<li class="dropdown">
							<a href="#" class="dropdown-toggle" data-toggle="dropdown" ><? echo tra ("Participants")?><b class="caret"></b></a>
								<ul class="dropdown-menu">
									<li><a tabindex="-1" href="home.php"><? echo tra("Your account") ?></a></li>
									<li><a tabindex="-1" href="uotd.php"><? echo tra("User of the day") ?></a></li>
									<li><a tabindex="-1" href="server_status.php"><?php echo tra("Server status") ?></a>
									<li><a tabindex="-1" href="team.php"><? echo tra("Teams") ?></a></li>
									<li><a tabindex="-1" href="cert1.php" target="_blank"><? echo tra("Certificate") ?></a></li>
									<li><a tabindex="-1" href="apps.php"><? echo tra("Applications") ?></a></li>
								</ul>
							</li>
							<li class="dropdown"> 
								<a href="#" class="dropdown-toggle" data-toggle="dropdown"><? echo tra("Community") ?><b class="caret"></b></a> 
								<ul class="dropdown-menu">  
									<li><a tabindex="-1" href="profile_menu.php"><? echo tra("Profiles") ?></a></li> 
									<li><a tabindex="-1" href="user_search.php"><? echo tra("User search") ?></a></li> 
									<li><a tabindex="-1" href="forum_index.php"><? echo tra("Message boards") ?></a></li> 
							<!--li><a tabindex="-1" href="forum_help_desk.php">questions and answers</a></li--> 
									<li class="dropdown-submenu"><a tabindex="-1" href="stats.php"><? echo tra("Statistics") ?></a> 
									<ul class="dropdown-menu"> 
										<li><a tabindex="-1" href="top_users.php"><? echo tra("Top participants") ?></a></li> 
										<li><a tabindex="-1" href="top_hosts.php"><? echo tra("Top computers") ?></a></li> 
										<li><a tabindex="-1" href="top_teams.php"><? echo tra("Top teams") ?></a></li> 
										<li><a tabindex="-1" href="gpu_list.php"><? echo tra("Top GPU models") ?></a></li> 
									</ul> 
							</li> 
							<li><a tabindex="-1" href="language_select.php"><? echo tra("Languages") ?></a></li> 
						</ul> 
					</li>
				</ul>
				<div class="nav-collapse collapse">
<?
$user = get_logged_in_user(false);
if($user){
        ?>
        <div class="btn-group pull-right">
          <button class="btn btn-primary" onclick="location.href='home.php'">
          <?php
                  echo $user->name;
          ?>
          </button>
					<a class="btn-danger btn" href='logout.php?<?php echo url_tokens($user->authenticator)?>'>log out</a>
				</div>
				<?
				}
				else{
       ?>
					<form class="navbar-form pull-right" method="post" action="login_action.php">
              <input type="hidden" name="next_url" value="home.php">
              <input class="span2" type="text" name="email_addr" placeholder="email">
              <input class="span2" type="password" name="passwd" placeholder="password">
              <button type="submit" class="btn btn-primary">Sign in</button>
            </form>
			<?
				}
			?>
			</div>
		</div>
	</div>
</div>
	<div class="container-fluid">
  	<div class="row-fluid">
       <div class="span12">
          <h1><? echo $title?></h1>
           <br />

	<?
}
function page_tail($show_date=false, $prefix="") {
?>
		</div>
		</div>
	</div>
	<br />
        <br />
        <br />
			<div class="navbar navbar-fixed-bottom ">
	<div class="navbar-inner">
	<ul class="nav pull-right">
	<li><a href="mailto:info@what.es"><?php echo "&copy;" . date("Y")." ".PROJECT; ?></a></li>
	</ul>
	</div>
	</div>
<?
}

