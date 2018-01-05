<?php


/**
 * Preprocesses the variables for esdivision.tpl.php.
 *
 * @see esdivision.tpl.php
 */
function template_preprocess_esignature_set_division(&$vars) {
	global $base_url;
	
	$vars['form_values'] = array();
	$vars['division'] = '';
	$vars['cache_id'] = '';
	if(isset($_REQUEST['division'])){
		$vars['division'] = $_REQUEST['division'];
		$vars['cache_id'] = $_REQUEST['cache_id'];
		if($vars['division']){
			$node = node_load($vars['division']);
			$vars['node'] = $node;
			$template = node_view($node);
			$vars['template'] = $template;
			
			$form_values['designation_line_1'] = (isset($template['field_designation_line_1']) ? $template['field_designation_line_1']['#items'][0]['value'] : '');
			$form_values['designation_line_2'] = (isset($template['field_designation_line_2']) ? $template['field_designation_line_2']['#items'][0]['value'] : '');
			
			$form_values['address'] = (isset($template['field_address']) ? $template['field_address']['#items'][0]['nid'] : '');
			$form_values['address_title'] = (isset($template['field_address']) ? $template['field_address']['0']['#title'] : '');
			$form_values['other'] = (isset($template['field_other']) ? $template['field_other']['#items'][0]['value'] : '');
			
			
			$form_values['telephone_ext'] = (isset($template['field_telephone_ext']) ? $template['field_telephone_ext']['#items'][0]['value'] : '');
			$form_values['telephone'] = (isset($template['field_telephone']) ? $template['field_telephone']['#items'][0]['value'] : '');
			$form_values['telephone_empty'] = (isset($template['field_telephone_empty']) ? $template['field_telephone_empty']['#items'][0]['value'] : '');
			
			
			$form_values['mobile_ext'] = (isset($template['field_mobile_ext']) ? $template['field_mobile_ext']['#items'][0]['value'] : '');
			$form_values['mobile'] = (isset($template['field_mobile']) ? $template['field_mobile']['#items'][0]['value'] : '');
			$form_values['mobile_empty'] = (isset($template['field_mobile_empty']) ? $template['field_mobile_empty']['#items'][0]['value'] : '');
			
			
			$form_values['fax_ext'] = (isset($template['field_fax_ext']) ? $template['field_fax_ext']['#items'][0]['value'] : '');
			$form_values['fax'] = (isset($template['field_fax']) ? $template['field_fax']['#items'][0]['value'] : '');
			$form_values['fax_empty'] = (isset($template['field_fax_empty']) ? $template['field_fax_empty']['#items'][0]['value'] : '');
			
			$form_values['email'] = (isset($template['field_email']) ? $template['field_email']['#items'][0]['value'] : '');	
			
			
			$form_values['skype'] = (isset($template['field_skype']) ? $template['field_skype']['#items'][0]['value'] : '');
			$form_values['skype_empty'] = (isset($template['field_skype_empty']) ? $template['field_skype_empty']['#items'][0]['value'] : '');
			
			
			$form_values['website'] = (isset($template['field_website']) ? $template['field_website']['#items'][0]['nid'] : '');	
			$form_values['website_title'] = (isset($template['field_website']) ? $template['field_website']['0']['#title'] : '');
			
			if(isset($template['field_main_image']) && $template['field_main_image']['#items'][0]['nid']){
				$main_image = node_load($template['field_main_image']['#items'][0]['nid']);
				$form_values['main_image'] = (isset($template['field_main_image']) ? $template['field_main_image']['#items'][0]['nid'] : '');
				$form_values['main_image_url_link'] = (isset($main_image->field_url_link) ? $main_image->field_url_link['und'][0]['value'] : '');
				$form_values['main_image_image_uri'] = (isset($main_image->field_mi_image) ? ($main_image->field_mi_image['und'][0]['uri']) : '');
				$form_values['main_image_image_url'] = (isset($main_image->field_mi_image) ? file_create_url($main_image->field_mi_image['und'][0]['uri']) : '');
				$form_values['main_image_image_name'] = (isset($main_image->field_mi_image) ? ($main_image->field_mi_image['und'][0]['filename']) : '');
			}
			
			if(isset($template['field_bottom_logo'])){
				foreach($template['field_bottom_logo']['#items'] as $val){
					$form_values['bottom_image'][] = $val['nid'];
					
					$bottom_image = node_load($val['nid']);
								
					$form_values['bottom_image_image_uri'][] = (isset($bottom_image->field_bl_image) ? ($bottom_image->field_bl_image['und'][0]['uri']) : '');
					$form_values['bottom_image_image_url'][] = (isset($bottom_image->field_bl_image) ? file_create_url($bottom_image->field_bl_image['und'][0]['uri']) : '');
					$form_values['bottom_image_image_name'][] = (isset($bottom_image->field_bl_image) ? ($bottom_image->field_bl_image['und'][0]['filename']) : '');
					$form_values['bottom_image_links'][] = (isset($bottom_image->field_bl_link) ? ($bottom_image->field_bl_link['und'][0]['value']) : '');
				}
			}
			
			$pattern = array();
			foreach($form_values as $k => $v){
				$pattern['{' . $k . '}'] = $v;
			}
			//set the empty value
			if(trim($form_values['telephone']) == ''){
				$pattern['{telephone}'] = '{telephone}';
				if(trim($form_values['telephone_empty'])){
					$pattern[$form_values['telephone_empty']]= '';
				}
			}else{
				$pattern['{telephone}'] = ($form_values['telephone_ext'] ? '+' . $form_values['telephone_ext'] . '' . $form_values['telephone'] : $form_values['telephone']);
			}
			
			if(trim($form_values['mobile']) == ''){
				$pattern['{mobile}'] = '{mobile}';
				if(trim($form_values['mobile_empty'])){
					$pattern[$form_values['mobile_empty']]= '';
				}
			}else{
				$pattern['{mobile}'] = ($form_values['mobile_ext'] ? '+' . $form_values['mobile_ext'] . '' . $form_values['mobile'] : $form_values['mobile']);
			}
			
			if(trim($form_values['fax']) == ''){
				$pattern['{fax}'] = '{fax}';
				if(trim($form_values['fax_empty'])){
					$pattern[$form_values['fax_empty']]= '';
				}
			}else{
				$pattern['{fax}'] = ($form_values['fax_ext'] ? '+' . $form_values['fax_ext'] . '' . $form_values['fax'] : $form_values['fax']);
			}
			
			if(trim($form_values['skype']) == ''){
				$pattern['{skype}'] = '{skype}';
				if(trim($form_values['skype_empty'])){
					$pattern[$form_values['skype_empty']]= '';
				}
			}else{
				$pattern['{skype}'] = $form_values['skype'];
			}
			//end set the empty value
			$pattern['{website}'] = $form_values['website_title'];		
			$pattern['{main_image}'] = '<a href="'. $form_values['main_image_url_link'] .'"><img border="0" src="'. $form_values['main_image_image_url'] . '"></a>';			
			$pattern['{address}'] = $form_values['address_title'];
			if(!$form_values['address_title']){
				$pattern['{address}'] = $form_values['other'];
			}
			$pattern['{bottom_image}'] = '';
			foreach($form_values['bottom_image_image_url'] as $index => $url){
				if($url){
					if(isset($form_values['bottom_image_links'][$index]) && $form_values['bottom_image_links'][$index]){
						$pattern['{bottom_image}'] .= '<a href="'. $form_values['bottom_image_links'][$index] .'"><img src="'. $url . '" /></a>';
					}else{
						$pattern['{bottom_image}'] .= '<img src="'. $url . '" />';
					}
				}
			}
						
			$form_values['body'] = $template['body']['#items'][0]['value'];
			$vars['pattern'] = $pattern;
			
			//prepare the theme file name
			$value = '';
			$form_values['directory'] = (isset($template['field_folder']) ? $template['field_folder']['#items'][0]['value'] : '');
			if($form_values['directory']){
				$form_values['full_directory'] = ESIGNATURE_TEMPLATE_DIRECTORY . $form_values['directory'];
				$form_values['full_directory_file'] =  ESIGNATURE_TEMPLATE_DIRECTORY . $form_values['directory'] . '/' . $vars['cache_id'] . '.html';
				$form_values['full_directory_filepath'] =  ESIGNATURE_TEMPLATE_DIRECTORY . $form_values['directory'] . '/' . $vars['cache_id'] . '.html';
				
				// Copy form values
				$form_values_apply = $form_values;
				
				// replace inline image
				$path = $base_url . '/' . $form_values_apply['full_directory'] . '/';
				$form_values_apply['body'] = str_replace('src="', 'src="' . $path, $form_values_apply['body']);
				
				//prepare the content
				$value = strtr($form_values_apply['body'], $vars['pattern']);
				
				//prepare the file
				// file_put_contents($form_values['full_directory_file'], $value);
				
			}
			
			$vars['form_values'] = $form_values;
				
			$_SESSION[$vars['cache_id']] = 
				serialize(
					array('pattern' => $pattern, 
					'form_values' => $form_values,
					'value' => $value,
				)
			);
		}
	}
	$vars['form'] = drupal_get_form('esignature_form', $vars['form_values'], $vars['cache_id']);
	$vars['bottom_image'] = esignature_form_bottom_imgae((isset($form_values['bottom_image']) ? $form_values['bottom_image'] : array()));
}

/**
 * implements theme_hook()
 */
function theme_esignature_set_item(&$vars){
	global $base_url;
	
	$vars['division'] = '';
	$vars['cache_id'] = '';
	if(isset($_REQUEST['division'])){
		$vars['division'] = $_REQUEST['division'];
		$vars['cache_id'] = $_REQUEST['cache_id'];
		
		if(!$_SESSION[$vars['cache_id']]){
			return FALSE;
		}
		
		$opt = unserialize($_SESSION[$vars['cache_id']]);
		//krumo($opt);
		$form_values = $opt['form_values'];
		$pattern = $opt['pattern'];
		
		if(isset($vars['reference']) && $vars['reference']){
			if($_REQUEST['item_name'] == 'address'){
				if($form_values[$_REQUEST['item_name']] == $_REQUEST['item_value']){
					$vars['not_reloaded'] = TRUE;
					return TRUE;
				}
			
				if($_REQUEST['item_value']){
					$obj = node_load($_REQUEST['item_value']);
					
					$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value'];
					$pattern['{' . $_REQUEST['item_name'] . '}'] = $obj->title;
				}else{
					$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value2'];
					$pattern['{' . $_REQUEST['item_name'] . '}'] = $_REQUEST['item_value2'];
				}
			}elseif($_REQUEST['item_name'] == 'website'){
				if($form_values[$_REQUEST['item_name']] == $_REQUEST['item_value']){
					$vars['not_reloaded'] = TRUE;
					return TRUE;
				}
				
				if($_REQUEST['item_value']){
					$obj = node_load($_REQUEST['item_value']);
					
					$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value'];
					$pattern['{' . $_REQUEST['item_name'] . '}'] = $obj->title;
				}else{
					$form_values[$_REQUEST['item_name']] = '';
					$pattern['{' . $_REQUEST['item_name'] . '}'] = '';
				}
			}elseif($_REQUEST['item_name'] == 'main_image'){
				if($form_values[$_REQUEST['item_name']] == $_REQUEST['item_value']){
					$vars['not_reloaded'] = TRUE;
					return TRUE;
				}
				
				if($_REQUEST['item_value']){
					$main_image = node_load($_REQUEST['item_value']);
					
					$form_values['main_image'] = $_REQUEST['item_value'];
					$form_values['main_image_url_link'] = (isset($main_image->field_url_link) ? ($main_image->field_url_link['und'][0]['value']) : '');
					$form_values['main_image_image_uri'] = (isset($main_image->field_mi_image) ? ($main_image->field_mi_image['und'][0]['uri']) : '');
					$form_values['main_image_image_url'] = (isset($main_image->field_mi_image) ? file_create_url($main_image->field_mi_image['und'][0]['uri']) : '');
					$form_values['main_image_image_name'] = (isset($main_image->field_mi_image) ? ($main_image->field_mi_image['und'][0]['filename']) : '');
					$pattern['{main_image}'] = '<a href="'. $form_values['main_image_url_link'] .'"><img src="'. $form_values['main_image_image_url'] . '" /></a>';
				}else{
					$pattern['{' . $_REQUEST['item_name'] . '}'] = '';
				}
			}elseif($_REQUEST['item_name'] == 'bottom_image'){
				if($form_values[$_REQUEST['item_name']] == $_REQUEST['item_value']){
					$vars['not_reloaded'] = TRUE;
					return TRUE;
				}
				
				if($_REQUEST['item_value']){
					$bottom_image_image_uri = array();
					$bottom_image_image_url = array();
					$bottom_image_image_name = array();
					$bottom_image_links = array();
					foreach($_REQUEST['item_value'] as $nid){
						if($nid){
							$bottom_image = node_load($nid);
								
							$bottom_image_image_uri[] = (isset($bottom_image->field_bl_image) ? ($bottom_image->field_bl_image['und'][0]['uri']) : '');
							$bottom_image_image_url[] = (isset($bottom_image->field_bl_image) ? file_create_url($bottom_image->field_bl_image['und'][0]['uri']) : '');
							$bottom_image_image_name[] = (isset($bottom_image->field_bl_image) ? ($bottom_image->field_bl_image['und'][0]['filename']) : '');
							$bottom_image_links[] = (isset($bottom_image->field_bl_link) ? ($bottom_image->field_bl_link['und'][0]['value']) : '');
						}else{
							$bottom_image_image_url[] = '';
							$bottom_image_image_name[] = '';
						}
					}
					
					$form_values['bottom_image'] = $_REQUEST['item_value'];
					$form_values['bottom_image_image_uri'] = $bottom_image_image_uri;
					$form_values['bottom_image_image_url'] = $bottom_image_image_url;
					$form_values['bottom_image_image_name'] = $bottom_image_image_name;
					$form_values['bottom_image_links'] = $bottom_image_links;
					
					$pattern['{bottom_image}'] = '';
					foreach($form_values['bottom_image_image_url'] as $index => $url){
						if($url){
							if(isset($form_values['bottom_image_links'][$index]) && $form_values['bottom_image_links'][$index]){
								$pattern['{bottom_image}'] .= '<a href="'. $form_values['bottom_image_links'][$index] .'"><img src="'. $url . '" /></a>';
							}else{
								$pattern['{bottom_image}'] .= '<img src="'. $url . '" />';
							}
						}
					}
				}else{
					$pattern['{' . $_REQUEST['item_name'] . '}'] = '';
				}
			}else{
				$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value'];
				$pattern['{' . $_REQUEST['item_name'] . '}'] = $_REQUEST['item_value'];
			}
		}else{	
			if($form_values[$_REQUEST['item_name']] == $_REQUEST['item_value']){
				$vars['not_reloaded'] = TRUE;
				return TRUE;
			}
		
			if($_REQUEST['item_name'] == 'other'){
				$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value'];
				$pattern['{address}'] = $_REQUEST['item_value'];
			}else{
				$form_values[$_REQUEST['item_name']] = $_REQUEST['item_value'];
				$pattern['{' . $_REQUEST['item_name'] . '}'] = $_REQUEST['item_value'];
			}
			
			if(in_array($_REQUEST['item_name'], array("telephone", "mobile", "fax"))){
				$pattern['{telephone}'] = ($form_values['telephone_ext'] ? '+' . $form_values['telephone_ext'] . '' . $form_values['telephone'] : $form_values['telephone']);
				
				$pattern['{mobile}'] = ($form_values['mobile_ext'] ? '+' . $form_values['mobile_ext'] . '' . $form_values['mobile'] : $form_values['mobile']);
				
				$pattern['{fax}'] = ($form_values['fax_ext']  ? '+' . $form_values['fax_ext'] . '' . $form_values['fax'] : $form_values['fax']);
			}
			
			//set the empty value
			if(trim($form_values['telephone']) == ''){
				$pattern['{telephone}'] = '{telephone}';
				if(trim($form_values['telephone_empty'])){
					$pattern[$form_values['telephone_empty']]= '';
				}
			}else{
				$pattern['{telephone}'] = ($form_values['telephone_ext'] ? '+' . $form_values['telephone_ext'] . '' . $form_values['telephone'] : $form_values['telephone']);
				unset($pattern[$form_values['telephone_empty']]);
			}
			
			if(trim($form_values['mobile']) == ''){
				$pattern['{mobile}'] = '{mobile}';
				if(trim($form_values['mobile_empty'])){
					$pattern[$form_values['mobile_empty']]= '';
				}
			}else{
				$pattern['{mobile}'] = ($form_values['mobile_ext'] ? '+' . $form_values['mobile_ext'] . '' . $form_values['mobile'] : $form_values['mobile']);
				unset($pattern[$form_values['mobile_empty']]);
			}
			
			if(trim($form_values['fax']) == ''){
				$pattern['{fax}'] = '{fax}';
				if(trim($form_values['fax_empty'])){
					$pattern[$form_values['fax_empty']]= '';
				}
			}else{
				$pattern['{fax}'] = ($form_values['fax_ext'] ? '+' . $form_values['fax_ext'] . '' . $form_values['fax'] : $form_values['fax']);
				unset($pattern[$form_values['fax_empty']]);
			}
			
			if(trim($form_values['skype']) == ''){
				$pattern['{skype}'] = '{skype}';
				if(trim($form_values['skype_empty'])){
					$pattern[$form_values['skype_empty']]= '';
				}
			}else{
				$pattern['{skype}'] = $form_values['skype'];
				unset($pattern[$form_values['skype_empty']]);
			}
			//end set the empty value
		}
		
		// Copy form values
		$form_values_apply = $form_values;
				
		// replace inline image
		$path = $base_url . '/' . $form_values_apply['full_directory'] . '/';
		$form_values_apply['body'] = str_replace('src="', 'src="' . $path, $form_values_apply['body']);
		
		// we modify image url		
		$value = str_ireplace('{main_image}', $pattern['{main_image}'], $form_values_apply['body']);
		
		//prepare the content
		$value = strtr($value, $pattern);
		// print($form_values['body']);
		// print_r($pattern);
		// print_r($value);
		// drupal_exit();
		//prepare the file
		file_put_contents($form_values['full_directory_file'], $value);
		// update 160708 store it to session
		
		
		$_SESSION[$vars['cache_id']] = 
			serialize(
				array(
					'pattern' => $pattern, 
					'form_values' => $form_values,
					'value' => $value,
				)
			);
		
		//exit;
		return TRUE;
	}
	return FALSE;
}