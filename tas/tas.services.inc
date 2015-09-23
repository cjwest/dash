<?php
/**
 * @file
 * Contains services for tas
 */

require_once DRUPAL_ROOT . '/sites/all/modules/custom/dash/includes/vendor/autoload.php';
use GuzzleHttp\Client;

/**
 * Get a client
 * @return Client
 */
function tas_get_client(){
  // Todo make this more efficient
  return new Client([
      'base_uri' => 'https://demo.theftalertsystem.com:8443/tas_console/include/api.php',
    ]
  );
}

/**
 * Wrapper function for refresh menu callback.
 */
function tas_refresh() {
  tas_update();
  drupal_set_message(t("Updated tasboard information."));
  //drupal_goto('admin/config/services/tas');
}

/**
 * Update the display
 */
function tas_update(){

  watchdog('tas', t("Begin updating tas information."));

  echo "Updating Tas information";
  $client = tas_get_client();

  $result = tas_get_version($client);
  var_dump($result);

  $result = tas_get_all_agents($client);
  var_dump($result);


  watchdog('tas', t("Finished updating tas information."));
}

/**
 * Get the version information
 * @param $client
 * @return mixed|string
 */
function tas_get_version($client) {
  $result = array();

  // Todo: put in exception handling
  $response = $client->get('?info=version');
  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to get info. Status code: ' . $status_code), WATCHDOG_WARNING);
  }
  else {
    return $response;
  }
  return $result;
}

/**
 * Get all the agents and return them in an array of agent entities.
 * @param $client
 * @return array
 */
function tas_get_all_agents($client) {
  $agents = array();
  $settings = tas_get_settings();

  // Todo: put in exception handling
  $response = $client->get(
    '?op=get&op2=all_agents&return_type=json&other_mode=url_encode_separator_|'
    . '&apipass=' . decrypt($settings['tas_apipass']) . '&user=' . $settings['tas_username'] . '&pass=' . decrypt($settings['tas_pass']));

  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to import agents. Status code: ' . $status_code), WATCHDOG_WARNING);
  }
  else {
    $result = json_decode($response->getBody(), true);
    if (!empty ($result)) {
      foreach ($result['data'] as $key => $value) {
        if ($result['data'][$key]['nombre'] == null || $result['data'][$key]['nombre'] == '')
        {
          watchdog('tas', t('No nombre or title for imported item: ' . $key), WATCHDOG_NOTICE);
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
  }
  return $agents;
}

/**
 * Get all the agents and their associated info.
 * @param $client
 * @return array
 */
function tas_get_all($client) {
  $agents = array();
  $settings = tas_get_settings();

  echo '*** Get all ***';
  $response = $client->get(
    '?op=get&op2=extension&ext_name=force_alerts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=rmt_ctl&pass=8765');
  // '?op=get&op2=extension&ext_name=force_alerts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=demo&pass=Dem04u! ');


  $content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
  $content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
  $content = $content . '<p>Body: ' . $response->getBody() . '</p>';
  echo $content;

  echo '*** decoding Json ***';
  $result = json_decode($response->getBody(), true);

  var_dump($result);

  // Todo: put in exception handling
//  $response = $client->get(
//   '?op=get&op2=extension&ext_name=force_alerts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|'
//    . '&apipass=5875&user=rmt_ctl&pass=8765');

//    '?op=get&op2=extension&ext_name=force_alerts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|'
//    . '&apipass=' . decrypt($settings['tas_apipass']) . '&user=' . $settings['tas_username'] . '&pass=' . decrypt($settings['tas_pass']));

//https://demo.theftalertsystem.com:8443/tas_console/include/api.php?op=get&op2=extension&ext_name=force_al erts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|&apipass=5875&user=demo&pass=Dem0 4u!
   /*
  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to import. Status code: ' . $status_code), WATCHDOG_WARNING);
  }
  else {
    var_dump($response);
    $result = json_decode($response->getBody(), true);

    var_dump($result);



    $result = json_decode($response->getBody(), true);
    if (!empty ($result)) {
      foreach ($result['data'] as $key => $value) {
        if ($result['data'][$key]['nombre'] == null || $result['data'][$key]['nombre'] == '')
        {
          watchdog('tas', t('No nombre or title for imported item: ' . $key), WATCHDOG_NOTICE);
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

  }
       */
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
function tas_tas_agent_entity_info() {
  $return = array(
    'agent' => array(
      'label' => t('Agent'),
      'controller class' => 'TasAgentController',
      'base table' => 'agent',
      'uri callback' => 'tas_agent_uri',
      'fieldable' => TRUE,
      'entity keys' => array(
        'id' => 'tas_agent_id',
        'label' => 'tas_agent_name',
      ),
      'bundles' => array(
        'tas_agent_entity_type' => array( // For the sake of simplicity, we only define one bundle.
          'label' => t('The Tas Agent entity type'),
          'admin' => array(
            'path' => 'admin/config/tas/tas_agent', // Field configuration pages for our entity will live at this address.
            'access callback' => 'tas_agent_access',
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
function tas_agent_uri($entity){
  return array('path' => 'tas_agent/' . $entity->identifier());
}


class TasAgentController extends EntityAPIController {

}

class TasAgent extends Entity {
  protected function defaultUri() {
    return array('path' => 'tas_agent/' . $this->identifier());
  }
}
*/

