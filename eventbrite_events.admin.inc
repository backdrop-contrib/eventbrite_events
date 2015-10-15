<?php

/**
 * @file
 * Contains the administration pages for Eventbrite Events Manager.
 *
 */

function eventbrite_events_admin_settings($form, &$form_state) {

  $form['eventbrite_events_display_link'] = array(
    '#type' => 'markup',
    '#title' => t('Manage display of event pages'),
    '#markup' => '<p>' . l(t('Manage display of event pages'), 'admin/structure/types/manage/eventbrite_event/display') . '</p>'
  );
  
  $form['eventbrite_events_info'] = array(
    '#type' => 'markup',
    '#title' => t('Event ticket widgets for your event pages.'),
    '#markup' => '<p>' . t('Step 1: enter your account information from above and save.<br>Step 2: sync your events.<br>Then, you may wish to choose a widget to add to the bottom of each public event page.  It is probably best practice to choose only one.  Widgets behave according to current date/status and Eventbrite rules and may not work as expected in all situations.') . '</p>'
  );
  
  $form['eventbrite_events_sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pull down your Eventbrite events into this site and sync'),
    '#description' => t('Check this box to pull down your Eventbrite events into this site and sync'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_sync'),
  );
  
  $form['eventbrite_events_ticketWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a ticket widget to your event pages'),
    '#description' => t('Check this box to attach a ticket badge to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_ticketWidget'),
  );
  
  $form['eventbrite_events_registrationWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a registration widget to your event pages'),
    '#description' => t('Check this box to attach a registration badge to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_registrationWidget'),
  );
  
  $form['eventbrite_events_calendarWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a calendar widget to your event pages'),
    '#description' => t('Check this box to attach a calendar badge to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_calendarWidget'),
  );
  
  $form['eventbrite_events_countdownWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a countdown widget to your event pages'),
    '#description' => t('Check this box to attach a countdown badge to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_countdownWidget'),
  );
  
  $form['eventbrite_events_buttonWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a button widget to your event pages'),
    '#description' => t('Check this box to attach a button to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_buttonWidget'),
  );
  
  $form['eventbrite_events_linkWidget'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach a link widget to your event pages'),
    '#description' => t('Check this box to attach a link to your event pages'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_linkWidget'),
  );
  
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}


function eventbrite_events_admin_keys($form, &$form_state) {
  $form['eventbrite_events_app_key'] = array(
    '#type' => 'textfield',
    '#title' => t('App Key'),
    '#description' => t('https://www.eventbrite.com/myaccount/apps'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_app_key'),
  );
  $form['eventbrite_events_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client Secret'),
    '#description' => t('https://www.eventbrite.com/myaccount/apps'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_client_secret'),
  );
  $form['eventbrite_events_user_key'] = array(
    '#type' => 'textfield',
    '#title' => t('User Key'),
    '#description' => t('http://www.eventbrite.com/userkeyapi'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_user_key'),
  );
  $form['eventbrite_events_token'] = array(
    '#type' => 'textfield',
    '#title' => t('User Token'),
    '#description' => t('https://www.eventbrite.com/myaccount/apps'),
    '#default_value' => config_get('eventbrite_events.settings', 'eventbrite_events_token'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Submit handler for module_settings_form().
 */
function eventbrite_events_admin_keys_submit($form, &$form_state) {
$config = config('eventbrite_events.settings');
foreach ($form_state['values'] as $key => $value)
{
$config->set($key, $value);
}

$config->save();
backdrop_set_message(t('The configuration options have been saved.'));
}


/**
 * Submit handler for module_settings_form().
 */
function eventbrite_events_admin_settings_submit($form, &$form_state) {

if ($form_state["values"]["eventbrite_events_sync"] === 1)
{
$app_key = config_get('eventbrite_events.settings', 'eventbrite_events_app_key');
$user_key = config_get('eventbrite_events.settings', 'eventbrite_events_user_key');
$app_token = config_get('eventbrite_events.settings', 'eventbrite_events_token');

if( isset($app_key) && isset($user_key) && isset($app_token) && ($app_key != "") && ($user_key != "") && ($app_token != ""))
{
$authentication_tokens = array('app_key'  => $app_key, 'user_key' => $user_key);
$eb_client = new Eventbrite( $authentication_tokens );
$events = $eb_client->user_list_events();

if( isset($events->events) ) {
  foreach( $events->events as $evnt ){

$query = new EntityFieldQuery;
$entities = $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'eventbrite_event')
  ->fieldCondition('field_eb_id', 'value', $evnt->event->id)
  ->execute();

if( empty( $entities ) )
{
$start_date = $evnt->event->start_date;
$end_date = $evnt->event->end_date;
$ddt = date_default_timezone();

$d = new DateTime($start_date, new DateTimeZone($ddt));
$d->setTimezone(new DateTimeZone('UTC'));
$utc_start = $d->format("Y-m-d H:i:s");

$d = new DateTime($end_date, new DateTimeZone($ddt));
$d->setTimezone(new DateTimeZone('UTC'));
$utc_end = $d->format("Y-m-d H:i:s");

$node = entity_create('node', array('type' => 'eventbrite_event'));
global $user;
$node->uid      = $user->uid;
$node->title    = $evnt->event->title;
$node->language = LANGUAGE_NONE;
$node->body[$node->language][0]['value'] = $evnt->event->description;
$node->status      = 1;
$eod = substr($evnt->event->organizer->description,0,254);

$node->field_eb_full_date[$node->language][0]['value'] =  $utc_start;
$node->field_eb_full_date[$node->language][0]['value2'] =  $utc_end;
$node->field_eb_full_date[$node->language][0]['timezone_db'] =  "UTC";
$node->field_eb_full_date[$node->language][0]['date_type '] =  "datetime";
$node->field_eb_num_attendee_rows[$node->language][0]['value'] = $evnt->event->num_attendee_rows;
$node->field_eb_tags[$node->language][0]['value'] = $theevent->event->tags;

$node->field_eb_id[$node->language][0]['value'] = $evnt->event->id;
$node->field_eb_status[$node->language][0]['value'] = $evnt->event->status;
$node->field_eb_start_date[$node->language][0]['value'] = $utc_start;
$node->field_eb_end_date[$node->language][0]['value'] = $utc_end;
$node->field_eb_locale[$node->language][0]['value'] = $evnt->event->locale;
$node->field_eb_timezone[$node->language][0]['value'] = $evnt->event->timezone;
$node->field_eb_timezone_offset[$node->language][0]['value'] = $evnt->event->timezone_offset;

$node->field_eb_organizer_name[$node->language][0]['value'] = $evnt->event->organizer->name;
$node->field_eb_organizer_id[$node->language][0]['value'] = $evnt->event->organizer->id;
$node->field_eb_organizer_description[$node->language][0]['value'] = $eod;
$node->field_eb_organizer_url[$node->language][0]['url'] = $evnt->event->organizer->url;
$node->field_eb_organizer_url[$node->language][0]['title'] = $evnt->event->organizer->name;

$node->field_eb_text_color[$node->language][0]['value'] = $evnt->event->text_color;
$node->field_eb_title_text_color[$node->language][0]['value'] = $evnt->event->title_text_color;
$node->field_eb_link_color[$node->language][0]['value'] = $evnt->event->link_color;
$node->field_eb_box_header_text_color[$node->language][0]['value'] = $evnt->event->box_header_text_color;
$node->field_eb_box_header_bg_color[$node->language][0]['value'] = $evnt->event->box_header_background_color;
$node->field_eb_box_border_color[$node->language][0]['value'] = $evnt->event->box_border_color;
$node->field_eb_box_background_color[$node->language][0]['value'] = $evnt->event->box_background_color;
$node->field_eb_background_color[$node->language][0]['value'] = $evnt->event->background_color;

$data = '';
$options = array(
                 'method' => 'GET',
                 'data' => $data,
                 'timeout' => 15
         );
$result = backdrop_http_request('https://www.eventbriteapi.com/v3/events/' . $evnt->event->id . '/?token=' . $app_token, $options);
if ($result->code == "200")
{
$theevent = $result->data;
$theevent = json_decode($theevent);
$node->field_eb_capacity[$node->language][0]['value'] = $theevent->capacity;
$node->field_eb_category[$node->language][0]['value'] = $theevent->category_id;
$node->field_eb_listed[$node->language][0]['value'] = $theevent->listed;
$node->field_eb_shareable[$node->language][0]['value'] = $theevent->shareable;
$node->field_eb_invite_only[$node->language][0]['value'] = $theevent->invite_only;
$node->field_eb_online_event[$node->language][0]['value'] = $theevent->online_event;
$node->field_eb_show_remaining[$node->language][0]['value'] = $theevent->show_remaining;
$node->field_eb_currency[$node->language][0]['value'] = $theevent->currency;
$node->field_eb_venue_id[$node->language][0]['value'] = $theevent->venue_id;
$node->field_eb_format_id[$node->language][0]['value'] = $theevent->format_id;
$node->field_eb_logo_id[$node->language][0]['value'] = $theevent->logo_id;
$node->save();
}
else
{
backdrop_set_message("Error processing the Eventbrite Event Url: " . $result->error . " " . $result->status_message, "warning");
}






}


  }
}
}
}

$config = config('eventbrite_events.settings');
foreach ($form_state['values'] as $key => $value)
{
$config->set($key, $value);
}

$config->save();
backdrop_set_message(t('The configuration options have been saved.'));
}
?>
