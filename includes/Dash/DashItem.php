<?php
/**
 * Created by PhpStorm.
 * User: cjwest
 * Date: 3/21/15
 * Time: 10:03
 */
namespace Dash;
//require_once 'includes/entity.inc';
require_once DRUPAL_ROOT . '/includes/entity.inc';
use GuzzleHttp\Collection;
use GuzzleHttp\Exception\ParseException;
//module_load_include('inc', 'entity', 'modules/callbacks');
//module_load_include('inc', 'entity', 'includes/entity.property');

class DashItem extends \Entity {

  public function __construct(array $values = array(), $entityType = 'dashboard_item') {
    parent::__construct($values, $entityType);

    // Expose settings for easier get access.
    if (isset($this->settings)) {
      $ar = $this->settings;
      if (!is_array($this->settings)) {
        $ar = unserialize($this->settings);
      }
      foreach ($ar as $key => $value) {
        if (!isset($this->{$key})) {
          $this->{$key} = $value;
        }
      }
    }
  }

  static public function getStatus($item) {
    $content = ' ';
    $error = false;

    $content = $content . '<p>URL: ' . $item->field_dash_item_url['und']['0']['url'] . '</p>';
    $content = $content . '<p>User: ' . $item->field_dash_item_user['und']['0']['safe_value'] . '</p>';
    $content = $content . '<p>Password: ' . $item->field_dash_item_password['und']['0']['safe_value'] . '</p>';


    $client = DashClient::factory(array(
      'base_url'        => $item->field_dash_item_url['und']['0']['url'],
      'consumer_key'    => $item->field_dash_item_user['und']['0']['safe_value'],
      'consumer_secret' => $item->field_dash_item_password['und']['0']['safe_value'],
    ));
    try {
      $res = $client->get($item->field_dash_item_url['und']['0']['url'],
        ['auth' =>  [$item->field_dash_item_user['und']['0']['safe_value'],
          $item->field_dash_item_password['und']['0']['safe_value']]]);
    } catch (\Exception $e) {
      $content = $content . "<p>Caught Exception: " . $e->getMessage() . '</p>';
      $error = true;
    }
    if ($error == false) {

      $content = $content . "<p>Status Code: " . $res->getStatusCode() . '</p>';
      $content = $content . '<p>Header: ' . $res->getHeader('content-type') . '</p>';
      $content = $content . '<p>Body: ' . $res->getBody() . '</p>';


      $item->body['und'][0]['value'] = $res->getBody();
      DashItem::_parseSirenJson($res->json());

      $node = node_submit($item);
      node_save($item);

    }


    var_export($res->json());
  }

  static private function _parseSirenJson($json){

    var_dump($json);

    global $user;

    $values = array(
      'type' => 'dash_siren',
      'uid' => $user->uid,
      'status' => 1,
    );
    $entity = entity_create('node', $values);
    $ewrapper = entity_metadata_wrapper('node', $entity);
    $ewrapper->title->set('YOUR TITLE');

    $my_body_content = 'A bunch of text about things that interest me';
    $ewrapper->body->set(array('value' => $my_body_content));

// Setting the value of an entity reference field only requires passing
// the entity id (e.g., nid) of the entity to which you want to refer
// The nid 15 here is just an example.
//    $ref_nid = 15;
// Note that the entity id (e.g., nid) must be passed as an integer not a
// string
//    $ewrapper->field_my_entity_ref->set(intval($ref_nid));

// Entity API cannot set date field values so the 'old' method must
// be used
//    $my_date = new DateTime('January 1, 2013');
//    $entity->field_my_date[LANGUAGE_NONE][0] = array(
//      'value' => date_format($my_date, 'Y-m-d'),
//      'timezone' => 'UTC',
//      'timezone_db' => 'UTC',
//    );

// Now just save the wrapper and the entity
// There is some suggestion that the 'true' argument is necessary to
// the entity save method to circumvent a bug in Entity API. If there is
// such a bug, it almost certainly will get fixed, so make sure to check.
    $ewrapper->save();

    return $json;
  }

}



