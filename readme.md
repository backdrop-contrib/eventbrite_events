Eventbrite Events
---------------------

This module allows you and your organization to showcase event info and sell event tickets from your website by hooking into the Eventbrite.com API.

This module uses version 3 of the Eventbrite API which is the current API of 2/2016.

CONTENTS OF THIS FILE
---------------------

 - Introduction
 - Tested
 - Known Issues
 - Special Thanks
 - Requirements
 - Installation
 - Coming From Drupal?
 - Usage
 - License
 - Credits
 - Maintainers

TESTED
-----

This module has been manually tested successfully creating and cloning events from the API in Backdrop 1.3.

You need existing Eventbrite events and API keys from that account to use this module.

KNOWN ISSUES
---------------------

This module does not create new events.

This module does not let you alter most fields of existing events.  The Eventbrite API will allow you to edit the description of the event among a few others but does not have a POST API for all event fields.  Because of this, many options are turned off for site users/content editors to prevent events getting out of sync between Eventbrite and your website.

Attendees are not yet implememted yet as I think about how they should be.  Ideas?  Post an issue on Github.

SPECIAL THANKS
--------------



REQUIREMENTS
------------

Libraries module
Date module
Link module
The third-party Eventbrite PHP library

INSTALLATION
------------

Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules

Visit https://github.com/ryanj/eventbrite.php and download the package there.

Place that into your site's libraries folder (in the root of your site, /libraries) the PHP library mentioned in the admin link

Make sure the name structure is /libraries/eventbrite/Eventbrite.php

Open up Eventbrite.php and comment out this line at the top "namespace Eventbrite;"

Open up admin/config/eventbrite_events on your website and configure your settings.


COMING FROM DRUPAL?
-------------------

This module is not a port from Drupal.

PERMISSIONS
------------

This module installs the following permissions:

Use Eventbrite Events
-- the ability to download events, slightly alter them, and sync them back

Edit and Clone Eventbrite Events
-- the ability to clone events to a different date, and sync them back

Access Eventbrite Keys
-- the ability to enter and view API keys to enable the module

USAGE
-----

You may think, "Why can't I just copy and paste some widget from the Eventbrite site which shows the last 3 events instead of this module?"  By installing this module, you can use the different fields of the events on Eventbrite in your own website Views for a more customized/personalized display.  In time, you can pull in a certain event's attendees with a click of a button on your website and then send bulk targeted emails to those attendees from your website.  You might enjoy different event displays with a click of a button:  sidebar lists, ticket buttons, calendars, etc...

If you wish to extend this module
https://www.eventbrite.com/developer/v3/

If you wish to learn more:
https://github.com/ryanj/eventbrite.php

We use the object oriented library to authenticate and get your user events and supplant that with a REST API GET request for each event.

We use the REST API to POST each event back to Eventbrite.

We encourage you to use this module as is or use it as an API base module.

Because a large number of event options are boolean true or false or large integer categories, and dates need to be changed between local time, Eventbrite time, and UTC time, it is not recommended to allow users to type in arbitrary information in to create events to Eventbrite.  Because of this, many event options/fields are read-only on your website.

LICENSE
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

CREDITS
-----------

Special thanks to:
https://github.com/ryanj
https://theeventscalendar.com
Automattic
Eventbrite

For their earlier Eventbrite efforts.

MAINTAINERS
-----------

- biolithic <https://github.com/biolithic>
