<?php
/**
 * @file
 * Contains services for tas
 */
// todo: remove these
//require_once("./" . drupal_get_path('module','tas') . "../includes/vendor/autoload.php");
//require_once DRUPAL_ROOT . '/sites/all/modules/custom/dash/includes/vendor/autoload.php';
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
  drupal_set_message(t("Updated tas dashboard information."));
  //drupal_goto('admin/config/services/tas');
}

/**
 * Update the display
 */
function tas_update() {

  watchdog('tas', t("Begin updating tas information."));

  echo "Updating Tas information";
  $client = tas_get_client();

  $result = tas_get_version($client);
  var_dump($result);

  $result = tas_get_all_agents($client);
  var_dump($result);

  $result = tas_update_nodes( $result);

  watchdog('tas', t("Finished updating tas information."));

}
/**
 * Update the nodes.
 */
/*
function tas_update_nodes($list = array()){
  if (!empty ($list)) {
    foreach ($list['data'] as $key => $value) {
      if ($list['data'][$key]['nombre'] == null || $list['data'][$key]['nombre'] == '')
      {
        watchdog('tas', t('No nombre or title for imported item: ' . $key), WATCHDOG_NOTICE);
      }
      else
      {
    $title = $data['id'];
    // Load the node that corresponds with the given check ID.
    // See https://www.drupal.org/node/1343708.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'stanford_dashboard_site')
      ->fieldCondition('field_s_site_id', 'value', $check_id, '=');
    $result = $query->execute();
    // There should be only one node with the given check_id
    if((isset($result['node'])) && (count($result['node']) == 1)) {
      // We can rely on the array key being the nid?
      reset($result['node']);
      $nid = key($result['node']);
      $node = node_load($nid);

      $entity_property_value_array = array();
      $entity_property_value_array['type'] = 'tas_agent';
      $entity_property_value_array['title'] = $list['data'][$key]['nombre'];
      $entity_property_value_array['body'] = $list['data'][$key]['comentarios'];
      $entity_property_value_array['field_tas_agent_id'] = $list['data'][$key]['id_agente'];
      $entity_property_value_array['field_tas_uri'] = $list['data'][$key]['direccion'];
      $entity_property_value_array['field_tas_name'] = $list['data'][$key]['name'];
      $entity_property_value_array['field_tas_url_address'] = $list['data'][$key]['url_address'];

      $agents[$key] = entity_create('node', $entity_property_value_array);
      //$agents[$key]->save();

      }
    }
  }
}
*/
function tas_update_nodes($list = array()){
  if (!empty ($list)) {
    foreach ($list['data'] as $key => $value) {
      if ($list['data'][$key]['nombre'] == null || $list['data'][$key]['nombre'] == '')
      {
        watchdog('tas', t('No nombre or title for imported item: ' . $key), WATCHDOG_NOTICE);
      }
      else
      {
        $node = tas_update_node($list['data'][$key]);
      }
    }
  }
}

function tas_update_node($data){
  $id = $data['id_agente'];
  // Try to load the node that corresponds with the given ID.
  // See https://www.drupal.org/node/1343708.

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'tas_agent')
    ->fieldCondition('field_tas_agent_id', 'value', $id, '=');
  $result = $query->execute();

  // It's brand-spankin' new!
  if(!isset($result['node'])) {
    $entity_property_value_array = array();
    $entity_property_value_array['type'] = 'tas_agent';
    $entity_property_value_array['title'] = $data['nombre'];
    $entity_property_value_array['body'] = $data['comentarios'];
    $entity_property_value_array['field_tas_agent_id'] = $data['id_agente'];
    $entity_property_value_array['field_tas_uri'] = $data['direccion'];
    $entity_property_value_array['field_tas_name'] = $data['name'];
    $entity_property_value_array['field_tas_url_address'] = $data['url_address'];

    $node = entity_create('node', $entity_property_value_array);
  }
  // Time for an update
  else {
    // Check that there's one node with the given id
    if(count($result['node']) > 1) {
      watchdog('tas', t('Warning: ' . count($result['node']) . ' entities with agent_id: ' . $id), WATCHDOG_WARNING);
      // Well, carry on but grab the first node.
      reset($result['node']);
    }
    $nid = key($result['node']);
    $node = node_load($nid);
    $node['type'] = 'tas_agent';
    $node['title'] = $data['nombre'];
    $node['body'] = $data['comentarios'];
    $node['field_tas_agent_id'] = $data['id_agente'];
    $node['field_tas_uri'] = $data['direccion'];
    $node['field_tas_name'] = $data['name'];
    $node['field_tas_url_address'] = $data['url_address'];
  }
  return node_save($node);
}

/**
 * Get the version information
 * @param $client
 * @return mixed|string
 */
function tas_get_version($client) {
  $list = array();

  // Todo: put in exception handling
  $response = $client->get('?info=version');
  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to get info. Status code: ' . $status_code), WATCHDOG_WARNING);
  }
  else {
    return $response;
  }
  return $list;
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
    return json_decode($response->getBody(), true);
  }
}
/*
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

 */

/**
 * Get all the agents and their associated info.
 * @param $client
 * @return array
 */
function tas_get_all($client) {
  $agents = array();
  $settings = tas_get_settings();
  $content = '';

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
  return $result;
}




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

  return $agents;
}
*/
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

