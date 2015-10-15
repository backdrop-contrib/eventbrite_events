Eventbrite Events
---------------------

This modules allows you and your organization to showcase and manage events from your website by hooking into the Eventbrite.com API.
This module uses version 3 of the Eventbrite API which is the current API of 10/2015.

You need existing Eventbrite events and API keys to use this module.

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

This module has been manually tested successfully creating and cloning events from the API in Backdrop 1.2.

KNOWN ISSUES
---------------------

This module works as is by just installing it, but requires existing Eventbrite events and API keys to use this module.
This module does not create new events.

As of 10/2/2015, cloning events screws up the time by several hours.  This is due to the multiple date changing that needs to happen to convert a date to local time, UTC, etc... back and forth between Eventbrite and the local MySQL database.  It takes brain power for me to figure this out, and this is hard to find after a day of work.  I'll solve it soon or you can write a patch.

Ticketing and attendees are not yet implememted yet as I think about how they should be.  Ideas?  Send an issue.

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

install into your site's libraries folder (in the root of your site, /libraries) the PHP library mentioned in the admin link

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

If you wish to extend this module
https://www.eventbrite.com/developer/v3/

If you wish to learn more:
https://github.com/ryanj/eventbrite.php

We use the object oriented library to authenticate and get your user events and supplant that with a REST API GET request for each event.

We use the REST API to POST each event back to Eventbrite.

We encourage you to use this module as is or use it as an API base module.

Because a large number of event options are boolean true or false or large integer categories, and dates need to be changed between local time, Eventbrite time, and UTC time, it is not recommended to allow users to type in arbitrary information in to create events to Eventbrite.

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
