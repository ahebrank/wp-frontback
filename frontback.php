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
