<?php
/**
 * @file
 * Contains services for dash
 */


require_once "includes/vendor/autoload.php";
use GuzzleHttp\Client;


/**
 * Wrapper function for refresh menu callback.
 */
function dash_refresh() {
  dash_update();
  drupal_set_message(t("Updated dashboard information."));
  //drupal_goto('admin/config/services/dash');
}

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

  // Todo: put in exception handling
$response = $client->get('?info=version');

var_dump($response);
$content = '';

$content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
$content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
$content = $content . '<p>Body: ' . $response->getBody() . '</p>';

  $result = dash_get_all_agents($client);

  var_dump($result);

  echo $content;

  watchdog('dash', t("Finished updating dash information."));
}

function dash_get_all_agents($client) {
  $agents = array();

  // Todo: put in exception handling
  $response = $client->get(
    '?op=get&op2=all_agents&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=rmt_ctl&pass=8765');

  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('dash', t('Unable to import agents. Status code: ' . $status_code), WATCHDOG_WARNING);
  }
  else {
    $result = json_decode($response->getBody(), true);

    var_dump($result);


    foreach ($result['data'] as $key => $value) {
      if ($result['data'][$key]['nombre'] == null || $result['data'][$key]['nombre'] == '')
      {
        watchdog('dash', t('No nombre or title for imported item: ' . $key), WATCHDOG_WARNING);
      }
      else
      {
        $entity_property_value_array = array();
        $entity_property_value_array['type'] = 'tas_agent';
        $entity_property_value_array['title'] = $result['data'][$key]['nombre'];
        $entity_property_value_array['body'] = $result['data'][$key]['comentarios'];
        $entity_property_value_array['field_tas_agent_id'] = $result['data'][$key]['id_agente'];
        $entity_property_value_array['field_tas_uri'] = $result['data'][$key]['direccion'];
        $entity_property_value_array['field_tas_name'] = $result['data'][$key]['name'];
        $entity_property_value_array['field_tas_url_address'] = $result['data'][$key]['url_address'];

        $agents[$key] = entity_create('node', $entity_property_value_array);
        //$agents[$key]->save();
      }

    }

  }
  return $agents;
}

/**
 * Create the agent entity
 * Note: I'm breaking this out since I anticipate more entities
 * @return array
 *
 *
 */
/*
function dash_tas_agent_entity_info() {
  $return = array(
    'agent' => array(
      'label' => t('Agent'),
      'controller class' => 'DashAgentController',
      'base table' => 'agent',
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
*
/**
 * Entity uri callback: points to a unique URI.
 */
/*
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
*/
