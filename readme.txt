=== Frontback ===
Tags: feedback, visual feedback, bug tracking, screenshot, image, images, plugin, bug, bugs, typo, screenshots, widget, bugtracking, issue tracking, project management, project tracking, bug tracker, development, testing, browser testing, website testing, wp plugin, acceptance test, acceptance testing, user testing, quality assurance, website widget, feedback widget, customer support, customer widget, survey form, screenshot widget, browser screenshot widget, bug reporter, qa, google, page, trello, JIRA, asana, basecamp, admin, administration, chat, slack, hipchat, hall, contact, form, dashboard, ecommerce, edit, content, css button, button, plugins, shortcode, fogbugz, redmine, github, desk, evernote, intercom, kanbanize, kanban, pivotal tracker, tracker, trac, bug tracker, bugs, feedback forms, notifications, notification, page screenshot, page previews, screenshot, screenshots, web page previews, visual items, user acceptance testing, uat, browser shots, browser shot, browser screenshots, browser screenshot, cross browser, cross browser testing, cross browser test
Requires at least: 3.0
Tested up to: 4.7

== Description ==

Report front end bugs with screenshots directly into your repo's issue tracker.

== Query Monitor Settings ==

FrontBack’s screenshot tool does not work very well if there are a lot of elements in the current page’s DOM. Unfortunately, the extremely useful Query Monitor plugin adds a ton of elements to the bottom of the page for debugging purposes.

To prevent Query Monitor from running when FrontBack is active, check "Disable Query Monitor by Default" in the FrontBack settings.

If you still want to run Query Monitor for specific accounts so that your developers can use it even when FrontBack is enabled, you can add the user logins for any allowed accounts in the "Allow Query Monitor for these acounts" setting. Separate each login with a comma. This setting will also allow you to enable Query Monitor for users that would not normally have access to it, e.g. users with the Editor role, so use the setting responsibly.

== Changelog ==

= 0.1 =
* intial version
