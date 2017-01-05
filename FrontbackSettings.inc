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
          array( $this, 'repo_id_callback' ), // Callback
          'frontback-setting-admin', // Page
          'frontback_options_main' // Section
      );

      add_settings_field(
          'endpoint',
          'Endpoint',
          array( $this, 'endpoint_callback' ),
          'frontback-setting-admin',
          'frontback_options_main'
      );
  }
  
  /**
    * field callbacks
    **/
  public function repo_id_callback()
  {
      printf(
          '<input type="text" id="repo_id" name="frontback_options[repo_id]" value="%s" />',
          isset( $this->options['repo_id'] ) ? esc_attr( $this->options['repo_id']) : ''
      );
  }
  public function endpoint_callback()
  {
      printf(
          '<input type="text" id="endpoint" name="frontback_options[endpoint]" value="%s" />',
          isset( $this->options['endpoint'] ) ? esc_attr( $this->options['endpoint']) : ''
      );
  }

}
