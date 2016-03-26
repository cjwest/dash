<?php
/**
 * @file
 * Contains services for tas
 */
use GuzzleHttp\Client;

/**
 * Get a client
 * @return Client
 */
function tas_get_client(){
  $settings = tas_get_settings();
  return new Client(['base_uri' => $settings['tas_base_uri']]);
}

/**
 * Wrapper function for refresh menu callback.
 */
function tas_refresh() {
  $count = tas_update();
  drupal_set_message(t("Updated @count TAS agents.", array('@count' => $count)));
  drupal_goto('admin/dash/tas'); // should go to a page displaying the agents instead...
}

/**
 * Update TAS data
 * @return number of agents
 */
function tas_update() {

  watchdog('tas', t("Begin updating tas information."), WATCHDOG_DEBUG);
  $client = tas_get_client();

  $agents_json = tas_get_all_agents($client);

  $agents_entities = tas_update_agents($agents_json);

  watchdog('tas', t("Finished updating tas information."), WATCHDOG_DEBUG);
  return count($agents_entities);

}
/**
 * Give an JSON array of agents, create if necessary or update the corresponding entity.
 * @return list of entities
 */
function tas_update_agents($list = array()){
  $entities = array();
  $count = 0;
  if (!empty ($list)) {
    foreach ($list['data'] as $key => $value) {
      if ($value['id_agente'] == null || $value['id_agente'] == '')
      {
        watchdog('tas', t('No id_agente for the imported item: @key', array('@key' => $key)), WATCHDOG_NOTICE);
      }
      else
      {
        $entities[$count] = tas_update_agent($value);
        $count++;
      }
    }
  }
  return $entities;
}
/**
 * Give an JSON array for an agent, create if necessary or update the corresponding entity.
 * @return entity
 */
function tas_update_agent($data){
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
    $entity = entity_create('node', $entity_property_value_array);
  }

  // Time for an update.
  else {
    // Warn if there's more than one node with the given id
    if(count($result['node']) > 1) {
      watchdog('tas', t('Warning: @count entities with agent_id: @id',
        array('@count' => count($result['node']), '@id' => $id)), WATCHDOG_WARNING);
      // Well, carry on but grab the first node.
      reset($result['node']);
    }
    $nid = key($result['node']);
    $entity = entity_load_single('node', $nid);
  }

  $wrapper = entity_metadata_wrapper('node', $entity);
  $wrapper->title = $data['nombre'];
  $wrapper->body->set(array('value' => $data['comentarios']));
  $wrapper->field_tas_agent_id = $data['id_agente'];
  $wrapper->field_tas_uri = $data['direccion'];
  $wrapper->field_tas_name = $data['name'];
  $wrapper->field_tas_url_address = $data['url_address'];
  return $wrapper->save();
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
    . '&apipass=' . decrypt($settings['tas_apipass'])
    . '&user=' . $settings['tas_username']
    . '&pass=' . decrypt($settings['tas_pass']));

  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to import agents. Status code: @status_code',
      array('@status_code' => $status_code)), WATCHDOG_WARNING);
  }
  else {
    return json_decode($response->getBody(), true);
  }
}
/**
 * Get all the agents and their associated info.
 * @param $response
 * @return array
 */
function tas_decode_response($response) {

  $content = '';
  $content = $content . "<p>Status Code: " . $response->getStatusCode() . '</p>';
  $content = $content . '<p>Header: ' . $response->getHeader('content-type') . '</p>';
  $content = $content . '<p>Body: ' . $response->getBody() . '</p>';
  echo $content;

  echo '*** decoding Json ***';
  $result = json_decode($response->getBody(), true);

  var_dump($result);
  return $result;
}
/**
 * Force a TAS alert
 * @param $client
 * @return array
 */
function tas_force_alert($client) {
  $settings = tas_get_settings();
  $response = $client->get(
    '?op=get&op2=extension&ext_name=force_alerts&ext_function=bogus_group_tree&return_type=json&other_mode=url_encode_separator_|'
      . '&apipass=' . decrypt($settings['tas_apipass'])
      . '&user=' . $settings['tas_username']
      . '&pass=' . decrypt($settings['tas_pass']));

  $status_code =  $response->getStatusCode();
  if ($status_code != 200){
    watchdog('tas', t('Unable to force alert. Status code: @status_code', array('@status_code' => $status_code)),
      WATCHDOG_WARNING);
  }
  else {
    return json_decode($response->getBody(), true);
  }
}

/**
 * Wrapper function for action menu callback.
 */
function tas_action($agent, $action) {
  $action = tas_build_action($agent, $action);
  echo $action;
  drupal_set_message(t("Sent TAS action: @action",  array('@action' => $action)));
  drupal_goto('admin/dash/tas'); // should go to a page displaying the agents instead...
}

function tas_build_action($agent, $action) {
  return $agent . ' ' . $action;
}