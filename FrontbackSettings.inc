<?php

class FrontbackSettings {
  private $options;
  
  public function __construct()
  {
      add_action( 'admin_menu', array( $this, 'add_plugin_page' ) );
      add_action( 'admin_init', array( $this, 'page_init' ) );
  }
  
  /**
   * Add options page
   */
  public function add_plugin_page()
  {
      // This page will be under "Settings"
      add_options_page(
          'Settings Admin',
          'Frontback',
          'manage_options',
          'frontback-setting-admin',
          array( $this, 'create_admin_page' )
      );
  }
  
  /**
   * Options page callback
   */
  public function create_admin_page()
  {
      $this->options = get_option( 'frontback_options' );
      require_once( FRONTBACK_ABSPATH . 'options.inc' );
  }
  
  /**
   * Register and add settings
   */
  public function page_init()
  {
      register_setting(
          'frontback_options',
          'frontback_options'
      );

      add_settings_section(
          'frontback_options_main',
          'Settings',
          array(),
          'frontback-setting-admin'
      );

      add_settings_field(
          'repo_id', // ID
          'Repository identifier', // Title
          array( $this, 'string_input_callback' ), // Callback
          'frontback-setting-admin', // Page
          'frontback_options_main', // Section
          array( 'id' => 'repo_id' )
      );

      add_settings_field(
          'endpoint',
          'Endpoint',
          array( $this, 'string_input_callback' ),
          'frontback-setting-admin',
          'frontback_options_main',
          array( 'id' => 'endpoint' )
      );

      add_settings_field(
        'login_required',
        'Show only for logged-in users',
        array( $this, 'boolean_input_callback' ),
        'frontback-setting-admin',
        'frontback_options_main',
        array( 'id' => 'login_required', 'default' => FALSE )
      );

      add_settings_field(
        'hideButton',
        'Hide Button',
        array( $this, 'boolean_input_callback' ),
        'frontback-setting-admin',
        'frontback_options_main',
        array( 'id' => 'hideButton', 'default' => FALSE )
      );

      add_settings_field(
        'hideReporterOptions',
        'Hide reporter dropdown',
        array( $this, 'boolean_input_callback' ),
        'frontback-setting-admin',
        'frontback_options_main',
        array( 'id' => 'hideReporterOptions', 'default' => FALSE )
      );

      add_settings_field(
        'hideAssigneeOptions',
        'Hide assignees',
        array( $this, 'boolean_input_callback' ),
        'frontback-setting-admin',
        'frontback_options_main',
        array( 'id' => 'hideAssigneeOptions', 'default' => FALSE )
      );

      add_settings_field(
        'disableQueryMonitor',
        'Disable Query Monitor by Default',
        array( $this, 'boolean_input_callback' ),
        'frontback-setting-admin',
        'frontback_options_main',
        array( 'id' => 'disable_qm', 'default' => FALSE )
      );

      add_settings_field(
          'qmAllowed', // ID
          'Allow Query Monitor for these accounts (comma separated)', // Title
          array( $this, 'string_input_callback' ), // Callback
          'frontback-setting-admin', // Page
          'frontback_options_main', // Section
          array( 'id' => 'qm_allow_list' )
      );
  }
  
  /**
    * field callbacks
    **/
  public function string_input_callback($args)
  {
      printf(
          '<input type="text" id="%s" name="frontback_options[%s]" value="%s" />',
          $args['id'], $args['id'],
          isset( $this->options[$args['id']] ) ? esc_attr( $this->options[$args['id']]) : ''
      );
  }

  public function boolean_input_callback($args)
  {
      $check_state = isset( $this->options[$args['id']] ) ? $this->options[$args['id']] : $args['default'];
      printf(
        '<input type="checkbox" id="%s" name="frontback_options[%s]" value="1" %s />',
        $args['id'], $args['id'],
        checked( TRUE, $check_state, FALSE)
      );
  }

}
