<?php
/*
Plugin Name: Frontback
Plugin URI: https://github.com/ahebrank/wp-frontback
Description: Submit frontend bug reports to Gitlab
Version: 0.1
Author: NewCity
Author URI: https://insidenewcity.com
License: GPL v2
*/

if(!defined('FRONTBACK_VERSION')) {
  define('FRONTBACK_VERSION', '0.1');
}
if(!defined('FRONTBACK_ABSPATH')) {
  define( 'FRONTBACK_ABSPATH', plugin_dir_path( __FILE__ ) );
}

/**
* add snippet
**/
function frontback_add_js() {
  $options = get_option('frontback_options');

  if (!is_user_logged_in() && isset($options['login_required'])) return;

  if (!isset($options['repo_id']) || empty($options['repo_id'])) return;
  if (!isset($options['endpoint']) || empty($options['endpoint'])) return;

  $opts = array(
    'hideButton' => FALSE,
    'hideReporterOptions' => FALSE,
    'hideAssigneeOptions' => FALSE,
    'disableQueryMonitor' => TRUE,
  );
  foreach ($opts as $k => $v) {
    $opts[$k] = isset($options[$k])? $options[$k] : $v;
  }
  $opts = json_encode($opts);
  
  $version = (time() - (time()%600)); // 10-min cache buster
  require_once(FRONTBACK_ABSPATH . 'snippet.inc');
}
add_action('wp_footer', 'frontback_add_js');
add_action('admin_footer', 'frontback_add_js');

if (is_admin()) {
  require_once(FRONTBACK_ABSPATH . 'FrontbackSettings.inc');
  $frontback_settings_path = new FrontbackSettings();
}

function frontback_query_monitor_settings(array $user_caps, array $required_caps, array $args, WP_User $user) {

  $options = get_option('frontback_options');
  do_action('qm/debug', $options);

  if ($options['disable_qm']) {
    // Remove QM capability from all users
    $user_caps['view_query_monitor'] = false; 
  }

  if (isset($options['qm_allow_list'])) {
    $allowed_accounts = explode(',', $options['qm_allow_list']);
    $allowed_accounts = array_map(function ($account) {
      return trim($account);
    }, $allowed_accounts);

    if (in_array($user->user_login, $allowed_accounts)) {
      $user_caps['view_query_monitor'] = true; 
    }
  }

  // Add QM capability for a single user named `admin`
  // if ($user->user_login === 'admin') {
  //     $user_caps['view_query_monitor'] = true;
  // }
  
  // // Add QM capability to a new user role called `developer`
  // if (in_array('developer', $user->roles)) {
  //     $user_caps['view_query_monitor'] = true;
  // }
  
  // // Remove QM capability from a single user named `dev_no_qm`
  // // (even if they have the `developer` role)
  // if ($user->user_login === 'dev_no_qm') {
  //     $user_caps['view_query_monitor'] = false;
  // }

  return $user_caps;
}
add_filter('user_has_cap', 'frontback_query_monitor_settings', 15, 4);
