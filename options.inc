<div class="wrap">
  <h1>Frontback</h1>
  <form method="post" action="options.php">
    <?php settings_fields( 'frontback_options' ); ?>
    <?php do_settings_sections( 'frontback-setting-admin' ); ?>
    <?php submit_button(); ?>
  </form>
</div>
