<?php

/**
 * @file
 * Administration callbacks for the lr_publish module
 */

// much of this is lifted from the "Creating Drupal 6.x modules" docs on the
// Drupal website http://drupal.org/node/231276 and the "Writing a Module"
// chapter of Pro Drupal Development 2nd Edition by John K. VanDyk.  ISBN-13:
// 978-1430209898

/**
 * Form builder. Configure lr_publish module.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function lr_publish_admin_settings() {
  // Get node types with internal names as keys and "friendly" names as
  // values.
  $options = node_get_types('names');

  $form = array();

  $form['lr_publish_node_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Learning Registry node URL'),
    '#size' => 128,
    '#maxlength' => 1024,
    '#default_value' => variable_get('lr_publish_node_url', NULL),
    '#description' => t('The URL of the Learning Registry node where data will be published.'),
    '#required' => TRUE,
  );

  // TODO: figure out if we need to validate this information.
  $form['lr_publish_submitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Submitter'),
    '#size' => 128,
    '#maxlength' => 1024,
    '#default_value' => variable_get('lr_publish_submitter', NULL),
    '#description' => t('Identifies the submitter of a Learning Registry resource document.'),
    '#required' => TRUE,
  );

  $form['lr_publish_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Publish metadata for these content types'),
    '#options' => $options,
    '#default_value' => variable_get('lr_publish_node_types', array()),
    '#description' => t('Metadata for these node types will be published to the specified Learning Registry node.'),
  );

  return system_settings_form($form);
}


/**
 * Validate the lr_publish configuration form.
 *
 * @param array $form
 *   The array that describes the configuration form.
 * @param array $form_state
 *   The values of the array.
 */
function lr_publish_admin_settings_validate($form, $form_state) {
  $lr_node_url = $form_state['values']['lr_publish_node_url'];
  if (!valid_url($lr_node_url, TRUE)) {
    form_set_error('lr_publish_node_url', t('Please provide a valid URL.'));
  }
}