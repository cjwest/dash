<?php
/**
 * @file
 * tas_agent.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function tas_agent_taxonomy_default_vocabularies() {
  return array(
    'tas_agent_group' => array(
      'name' => 'TAS Agent Group',
      'machine_name' => 'tas_agent_group',
      'description' => 'Vocabulary for grouping for TAS agents',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'tas_agent_status' => array(
      'name' => 'TAS Agent Status',
      'machine_name' => 'tas_agent_status',
      'description' => 'Vocabulary to identify TAS agent status',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
