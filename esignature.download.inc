<?php

function esignature_generator_download_callback($cache_id, $division){
	global $base_url;
	
	ob_start();
	
	$msg = array();
	
	// try{

		//load the session data	
		if(!$_SESSION[$cache_id]){
			$msg[] = 'Error, the session has been expires. Please try again.';
			throw new Exception('5');
		}
		
		$opt = unserialize($_SESSION[$cache_id]);
		$form_values = $opt['form_values'];
		$pattern = $opt['pattern'];
		
		
		//load all resource to temp directory
		$temp = file_directory_temp() . '/';
		$dir = $temp . $cache_id;
		
		//create directory
		if(!is_dir($dir)){
			if(!mkdir($dir)){
				watchdog('e-signature', 'Error make new directory of "'.$cache_id.'".', NULL, WATCHDOG_ERROR);
				$msg[] = 'Error while process your zipped file. Please try again.';
				throw new Exception('5');
			}
		}
		
		$temp_filename = $cache_id . '.html';
		$temp_file = $dir . '/' . $cache_id . '.html';

		$zfiles = array();
		//$zfiles[$form_values['full_directory_file']] = 'index.html';
		$zfiles[$form_values['full_directory_file']] = trim($form_values['email']) . '.htm';
		
		//copy all file from template directory into $dir
		$files = scandir($form_values['full_directory']);
		foreach($files as $file){
			if($file != '.' && $file != '..' && substr($file, -4) != 'html' && substr($file, -4) != '.zip' && !is_dir($file)){
				//$fdest = $dir . '/' . $file;
				$filefrom = $form_values['full_directory'] . '/' . $file;
				$zfiles[$filefrom] = $file;
				//esignature_copy($file, $fdest);
			}
		}
		
		//copy main_image_image_uri
		if(isset($form_values['main_image_image_uri']) && $form_values['main_image_image_uri']){
			$file = drupal_realpath($form_values['main_image_image_uri']);
			//esignature_copy($file, $dir . '/' . $form_values['main_image_image_name']);
			
			$zfiles[$file] = $form_values['main_image_image_name'];
			
			if(isset($_GET['mode']) && $_GET['mode'] == 'online'){
				$form_values['main_image_image_name'] = file_create_url($form_values['main_image_image_uri']);
			}
		}
		
		//bottom logo
		if(isset($form_values['bottom_image_image_uri']) && is_array($form_values['bottom_image_image_uri'])){
			if($form_values['bottom_image_image_uri']){
				for ($i = 0; $i < count($form_values['bottom_image_image_uri']); $i ++){
					$file = drupal_realpath($form_values['bottom_image_image_uri'][$i]);
					//esignature_copy($file, $dir . '/' . $form_values['bottom_image_image_name'][$i]);
					$zfiles[$file] = $form_values['bottom_image_image_name'][$i];
					
					if(isset($_GET['mode']) && $_GET['mode'] == 'online'){
						$form_values['bottom_image_image_name'][$i] = file_create_url($form_values['bottom_image_image_uri'][$i]);
					}
				}
			}
		}  
		
		$pattern['{main_image}'] = '<a href="'. $form_values['main_image_url_link'] .'"><img border="0" src="'. $form_values['main_image_image_name'] . '" data-image_name="'. $form_values['main_image_image_name'] . '" /></a>';
		$pattern['{bottom_image}'] = '';
		if(isset($form_values['bottom_image_image_name']) && is_array($form_values['bottom_image_image_name'])){
			foreach($form_values['bottom_image_image_name'] as $index => $url){
				if($url){
					if(isset($form_values['bottom_image_links'][$index]) && $form_values['bottom_image_links'][$index]){
						$pattern['{bottom_image}'] .= '<a href="'. $form_values['bottom_image_links'][$index] .'"><img src="'. $url . '" /></a>';
					}else{
						$pattern['{bottom_image}'] .= '<img src="'. $url . '" />';
					}
				}
			}
		}
		
		// replace inline image
		if(isset($_GET['mode']) && $_GET['mode'] == 'online'){
			$path = $base_url . '/' . $form_values['full_directory'] . '/';
			$form_values['body'] = str_replace('src="', 'src="' . $path, $form_values['body']);
		}
		
		// we modify main image first
		$value = str_ireplace('{main_image}', $pattern['{main_image}'], $form_values['body']);
		
		//prepare the content
		$value = strtr($value, $pattern);
		
		//prepare the file
		file_put_contents($form_values['full_directory_file'], $value);
		
		//make zip file
		// krumo($zfiles);
		// exit;
		//$zip = 'sites/default/templates/esignature.zip';
		$zip = $form_values['full_directory'] . '/esignature.zip';
		if(!create_zip($zfiles, $zip, true)){
			$msg[] = 'Error while create your zipped file. Please try again.';
			// throw new Exception('5');
		}
		
		set_time_limit(0);
		
		$fsize = filesize($zip);
		
				
		// $fname = esignature_generate_slug(($form_values['name'] ? $form_values['name'] : 'no name')) . '.zip';
		$fname = trim($form_values['email']) . '.zip';
		header("Pragma: public");
		header("Expires: 0");
		header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
		header("Cache-Control: public");
		header("Content-Description: Signature File");
		header("Content-Type: archive/zip");
		header('Content-Disposition: attachment; filename="'.$fname.'"');
		//header("Content-Transfer-Encoding: binary");
		//header("Content-Length: " . $fsize);
		
		// Update because on mac becomes cpgz
		ob_clean();
		$fopen_zip = fopen($zip, "r");
		echo fpassthru($fopen_zip);
		unlink($zip);
		drupal_exit();
		// $file = @fopen($zip, "rb");
		// if ($file) {
			// while(!feof($file)) {
				// print(fread($file, 1024));
				// flush();
				// if (connection_status() != 0) {
					// @fclose($file);
					// die();
				// }
			// }
			// @fclose($file);
			// unlink($zip);
		// }
		
	// }catch(Exception $e){
		// foreach($msg as $val){
			// drupal_set_message($val, 'error');
		// }
		// return 'Error downloading zip file.';
	// }
}

function esignature_copy($file, $fdest){
	if(file_exists($fdest)){
		unlink($fdest);
	}
	if(! copy($file, $fdest)){
		watchdog('e-signature', 'Error copy file '. $file, NULL, WATCHDOG_ERROR);
	}
}


?>
