<?php
/**
 * @file
 * Contains services for dash
 */

require_once "includes/vendor/autoload.php";
use GuzzleHttp\Client;
/**
 * Update the display
 */
function dash_update(){

  watchdog('dash', t("Begin updating dash information."));

echo "Updating Dash information";

$client = new Client([
    'base_uri' => 'https://demo.theftalertsystem.com:8443/tas_console/include/api.php',
  ]
);
$response = $client->get('?info=version');

var_dump($response);
$content = '';

$content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
$content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
$content = $content . '<p>Body: ' . $response->getBody() . '</p>';



$response = $client->get(
  '?op=get&op2=all_agents&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=rmt_ctl&pass=8765');

$content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
$content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
$content = $content . '<p>Body: ' . $response->getBody() . '</p>';

$result = json_decode($response->getBody(), true);

var_dump($result);

  echo $content;

  watchdog('dash', t("Finished updating dash information."));
}

/**
 * Implements hook_entity_info().
 */
function dash_entity_info() {
  return _dash_agent_entity_info();
}

/**
 * Create the agent entity
 * Note: I'm breaking this out since I anticipate more entities
 * @return array
 *
 *
 */
function _dash_agent_entity_info() {
  $return = array(
    'dash_agent' => array(
      'label' => t('Dash Agent'),
      'controller class' => 'DashAgentController',
      'base table' => null,
      'uri callback' => 'dash_agent_uri',
      'fieldable' => TRUE,
      'entity keys' => array(
        'id' => 'dash_agent_id',
        'label' => 'dash_agent_name',
      ),
      'bundles' => array(
        'dash_agent_entity_type' => array( // For the sake of simplicity, we only define one bundle.
          'label' => t('The Dash Agent entity type'),
          'admin' => array(
            'path' => 'admin/config/dash/dash_agent', // Field configuration pages for our entity will live at this address.
            'access callback' => 'dash_agent_access',
          ),
        ),
      ),
      'view modes' => array(
        'full' => array(
          'label' => t('Default'),
          'custom settings' => FALSE,
        ),
      ),
    ),
  );

  return $return;
}
/**
 * Entity uri callback: points to a unique URI.
 */
function dash_agent_uri($entity){
  return array('path' => 'dash_agent/' . $entity->identifier());
}


class DashAgentController extends EntityAPIController {

}

class DashAgent extends Entity {
  protected function defaultUri() {
    return array('path' => 'dash_agent/' . $this->identifier());
  }
}