<script>
  (function() {
    window.frontback = {
      repo: '<?=$options['repo_id']?>',
      postUrl: '<?=$options['endpoint']?>',
      options: <?=$opts?>,
    };
    var frontbackVersion = '<?=$version?>';

    var s = document.createElement('script'),
        x = document.getElementsByTagName('script')[0];
    var script = document.createElement('script');
    script.src = frontback.postUrl + '/assets/js/frontback.js?v=' + frontbackVersion;
    document.body.appendChild(script);
  })();
</script>
