<?php



if($division == ''){

?>
<script type="text/javascript" src="<?php print base_path() . drupal_get_path('module', 'esignature'); ?>/generator.js"></script>
<div id="esignature">
	<form id="form-esignature" action="">
		<?php print render($form['cache_id']); ?>
		<?php print render($form['division']); ?>
		
		<div id="form-applied-wrapper">
			<div class="left">
			
			</div>
			<div class="right">
				<h3>Preview</h3>
				<div id="preview-loading"></div>
				<div id="preview">
					
				</div>
			</div>
		</div>
	</form>
</div>
<?php }elseif(!$division){ ?>
			<div class="left">
			
			</div>
			<div class="right">
				<h3>Preview</h3>
				<div id="preview-loading"></div>
				<div id="preview">
					
				</div>
			</div>
<?php }else{ ?>
			<div class="left">
				<div class="item-group">
					<?php print render($form['name']); ?>
					<?php print render($form['designation_line_1']); ?>
					<?php print render($form['designation_line_2']); ?>
				</div>
						
				<div class="item-group">
					<?php print render($form['address']); ?>
					<?php print render($form['other']); ?>
				</div>
				
				<div class="item-group">
					<div class="item-group-wrapper">
						<label>Telephone</label>
						<span class="sparate">+ </span>
						<?php print render($form['telephone_ext']); ?>
						<span class="sparate"></span>
						<?php print render($form['telephone']); ?>
						<div class="clear"></div>
					</div>
					<div class="item-group-wrapper">
						<label>Mobile</label>
						<span class="sparate">+ </span>
						<?php print render($form['mobile_ext']); ?>
						<span class="sparate"></span>
						<?php print render($form['mobile']); ?>
						<div class="clear"></div>
					</div>
					<div class="item-group-wrapper">
						<label>Fax</label>
						<span class="sparate">+ </span>
						<?php print render($form['fax_ext']); ?>
						<span class="sparate"></span>
						<?php print render($form['fax']); ?>
						<div class="clear"></div>
					</div>
				</div>

				<div class="item-group">
					<?php print render($form['email']); ?>
					<?php print render($form['skype']); ?>
					<?php print render($form['website']); ?>
				</div>
				
				<div class="item-group">
					<?php print render($form['main_image']); ?>
				</div>
				
				<div class="item-group">
					<?php print $bottom_image; ?>
				</div>
			</div>
			<div class="right">
				<h3>Preview</h3>
				<div id="preview-loading"></div>
				<div id="preview">
					<?php if($division){ ?>
						<iframe id="preview_iframe" src="<?php print base_path() . 'admin/esignature/generator/view/' . $division; ?>?cache_id=<?php echo $cache_id; ?>">
						</iframe>
						<a class="dowload_preview" href="<?php print base_path() . 'admin/esignature/generator/download/' . $cache_id . '/' . $division;  ?>">Download</a> 
						<a class="dowload_preview" href="<?php print base_path() . 'admin/esignature/generator/download/' . $cache_id . '/' . $division . '?mode=online';  ?>">Download for Mac</a>
					<?php } ?>
				</div>
			</div>
<?php } ?>