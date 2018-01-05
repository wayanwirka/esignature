<?php

function esignature_templates_callback(){
	return views_embed_view('templates', 'default');
}

function esignature_templates_address_callback(){
	drupal_set_title('Address');
	return views_embed_view('address', 'default');
}

function esignature_templates_website_callback(){
	drupal_set_title('Website');
	return views_embed_view('websites', 'default');
}

function esignature_templates_main_image_callback(){
	drupal_set_title('Main Image');
	return views_embed_view('main_image', 'default');
}

function esignature_templates_bottom_logo_callback(){
	drupal_set_title('Bottom Logo');
	return views_embed_view('bottom_logo', 'default');
}


//========================TEMPLATE CREATOR========================
{
	/**
	 * 
	 */
	function esignature_signature_image_callback($nid){
		drupal_add_js(base_path() . drupal_get_path('module', 'esignature') . '/jquery.form.js');		
		drupal_add_js(base_path() . drupal_get_path('module', 'esignature') . '/generator.js');
		
		//$node = node_load($nid);
		//krumo($node);
		return esignature_upload_image_form($nid);
	}
	
	function esignature_upload_image_form($nid){
		$node = node_load($nid);
		//$dir = base_path() . ESIGNATURE_TEMPLATE_DIRECTORY . $node->field_folder['und'][0]['value'];
		$dir = ESIGNATURE_TEMPLATE_DIRECTORY . $node->field_folder['und'][0]['value'];
		
		$types = array('image/jpeg', 'image/gif');
		$validfiles = array();
		if(is_dir($dir)){
			$files = scandir($dir);
			foreach($files as $file){
				if(substr($file, -5) == '.jpeg' || substr($file, -4) == '.jpg' || substr($file, -4) == '.gif'){
					$fullpath = $dir . '/' . $file;
					$validfiles[$file] = $fullpath;
				}
			}
		}
		
		$out = '		
			<form method="post" id="form_image_upload" name="form_images" action="'.base_path().'node/'. $nid .'/signature/images/upload">
				<ul class="process-tab">
					<li class="stept first">Upload Template</li>
					<li class="arrow-right inactive"></li>
					<li class="stept last active">Upload Images</li>
					<li class="arrow-right last"></li>
				</ul>
				<div class="clear"></div>
				<div id="images-upload-editor">
					<label for="field_image_location">Image Location<label><input type="file" name="image" value="" class="input file form-text" id="field_image_location" />
					<input type="submit" name="upload" value="Upload" class="form-submit">
					<a href="'.base_path().'admin/esignature/settings/templates" class="button">Complate</a>
				</div>
				<div id="images-uploaded">';
				foreach($validfiles as $filename => $fullpath){
					$out .= '
						<div class="item_image_uploaded">
							<a class="remove-image" href="'.base_path().'node/'.$nid.'/signature/images/delete/'.$filename.'">X</a>
							<div class="image">
								<img src="'.base_path() . $fullpath .'" />
							</div>
							<div class="desc">
								'.$filename.'
							</div>
						</div>
					';
				}
		$out .= '
				</div>
			</form>
		';
		
		return $out;
	}
	
	function esignature_signature_image_upload_callback($nid){
		$res = array();
		try{
			if(! $nid){
				$res['error'][] = 'Error, the template is not defined.';
				throw new Exception('1');
			}
			$node = node_load($nid);
			
			$types = array('image/jpeg', 'image/gif');
			
			if(! in_array($_FILES['image']['type'], $types)){
				$res['error'][] = 'Error, image file is invalid format.';
				throw new Exception('1');
			}
			
			//create directory			
			if(!count($node->field_folder['und'])){
				$res['error'][] = 'Error, the folder of templpate is not initialized.';
				throw new Exception('1');
			}
			
			$tmp = $_FILES['image']['tmp_name'];
			
			$dir = ESIGNATURE_TEMPLATE_DIRECTORY . $node->field_folder['und'][0]['value'];
			$filename = $_FILES['image']['name'];
			$filedir = $dir . '/' . $filename;
			
			if(! file_exists($dir)){
				if(! mkdir($dir)){
					$res['error'][] = 'Error, while make new template directory.';
					throw new Exception('1');
				}
			}
			
			if(file_exists($filedir)){
				$res['error'][] = 'Error, this filename has been exists.';
				throw new Exception('1');
			}
			
			if(! move_uploaded_file($tmp, $filedir)){
				$res['error'][] = 'Error uploading your file.';
				throw new Exception('1');
			}
			
			$res['result'] = TRUE;
			$res['content'] = '
				<div class="item_image_uploaded">
					<a class="remove-image" href="'.base_path().'node/'.$nid.'/signature/images/delete/'.$filename.'">X</a>
					<div class="image">
						<img src="'.base_path() . $filedir .'" />
					</div>
					<div class="desc">
						'.$filename.'
					</div>
				</div>
			';
			
			return drupal_json_output($res);
					
		}catch(Exception $e){
			$res['result'] = FALSE;			
			return drupal_json_output($res);
		}
	}
	
	function esignature_signature_image_delete_callback($nid, $filename){
		$res = array();
		try{
			if(! $nid){
				$res['error'][] = 'Error, the template is not defined.';
				throw new Exception('1');
			}
			$node = node_load($nid);
			
			$dir = ESIGNATURE_TEMPLATE_DIRECTORY . $node->field_folder['und'][0]['value'];
			$filedir = $dir . '/' . $filename;
			
			if(! file_exists($dir)){
				$res['error'][] = 'Error, template directory does not found.';
				throw new Exception('1');
			}
			
			unlink($filedir);
			
			$res['result'] = TRUE;
			
			return drupal_json_output($res);
		}catch(Exception $e){
			$res['result'] = FALSE;
			return drupal_json_output($res);
		}
	}
}

?>