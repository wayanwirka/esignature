/*
 * jQuery hashchange event - v1.3 - 7/21/2010
 * http://benalman.com/projects/jquery-hashchange-plugin/
 * 
 * Copyright (c) 2010 "Cowboy" Ben Alman
 * Dual licensed under the MIT and GPL licenses.
 * http://benalman.com/about/license/
 */
(function($,e,b){var c="hashchange",h=document,f,g=$.event.special,i=h.documentMode,d="on"+c in e&&(i===b||i>7);function a(j){j=j||location.href;return"#"+j.replace(/^[^#]*#?(.*)$/,"$1")}$.fn[c]=function(j){return j?this.bind(c,j):this.trigger(c)};$.fn[c].delay=50;g[c]=$.extend(g[c],{setup:function(){if(d){return false}$(f.start)},teardown:function(){if(d){return false}$(f.stop)}});f=(function(){var j={},p,m=a(),k=function(q){return q},l=k,o=k;j.start=function(){p||n()};j.stop=function(){p&&clearTimeout(p);p=b};function n(){var r=a(),q=o(m);if(r!==m){l(m=r,q);$(e).trigger(c)}else{if(q!==m){location.href=location.href.replace(/#.*/,"")+q}}p=setTimeout(n,$.fn[c].delay)}$.browser.msie&&!d&&(function(){var q,r;j.start=function(){if(!q){r=$.fn[c].src;r=r&&r+a();q=$('<iframe tabindex="-1" title="empty"/>').hide().one("load",function(){r||l(a());n()}).attr("src",r||"javascript:0").insertAfter("body")[0].contentWindow;h.onpropertychange=function(){try{if(event.propertyName==="title"){q.document.title=h.title}}catch(s){}}}};j.stop=k;o=function(){return a(q.location.href)};l=function(v,s){var u=q.document,t=$.fn[c].domain;if(v!==s){u.title=h.title;u.open();t&&u.write('<script>document.domain="'+t+'"<\/script>');u.close();q.location.hash=v}}})();return j})()})(jQuery,this);

jQuery(document).ready(function($){
	var inited = false;
	
	$(document).delegate('#edit-division', 'change', function(){
		division_changed();
	});
	
	//if division has value
	if($('#edit-division').find('option:selected').val()){
		division_changed();
	}
	
	function division_changed(){
		if(inited)
			window.location.hash = '#' + $('#edit-division').find('option:selected').val();
		
		$('#preview-loading').fadeIn();
		$.ajax({
			type: 'POST',
			url: Drupal.settings.basePath + 'admin/esignature/generator',
			dataType: 'json',
			data: {
					division : $('#edit-division').find('option:selected').val(), 
					cache_id : $('input[name="cache_id"]').val()
				},
			success: function(res){
				$('#preview-loading').fadeOut();
				if(res.result){
					$('#form-applied-wrapper').html(res.output);
					if($('#edit-address').find('option:selected').val()){
						$('.form-item-other').slideUp('normal');
					}
				}
			}
		});	
	}	
	
	$(document).delegate('input[type="text"]', 'focusout', function(){
		var vname = $(this).attr('name');
		var vvalue = $(this).val();
		var vcache_id = $('input[name="cache_id"]').val();
		var vdivision = $('#edit-division').find('option:selected').val();
		
		
		$('#preview-loading').fadeIn();
		$.ajax({
			type: 'POST',
			url: Drupal.settings.basePath + 'admin/esignature/generator/item',
			dataType: 'json',
			data: {
					division : vdivision + '', 
					cache_id : vcache_id + '',
					item_name : vname + '',
					item_value : vvalue + ''
				},
			success: function(res){
				$('#preview-loading').fadeOut();
				if(res.result){
					document.getElementById('preview_iframe').contentDocument.location.reload(true);
				}
			}
		});	
	});
	//address selectbox
	$(document).delegate('#edit-address', 'change', function(){
		var vname = $(this).attr('name');
		var vvalue = $(this).find('option:selected').val();
		var vvalue2 = $('#edit-other').val();
		var vcache_id = $('input[name="cache_id"]').val();
		var vdivision = $('#edit-division').find('option:selected').val();
		
		if(! vvalue){
			$('.form-item-other').slideDown('normal');
		}else{
			$('.form-item-other').slideUp('normal');
		}
		
		
		$('#preview-loading').fadeIn();
		$.ajax({
			type: 'POST',
			url: Drupal.settings.basePath + 'admin/esignature/generator/item_ref',
			dataType: 'json',
			data: {
					division : vdivision + '', 
					cache_id : vcache_id + '',
					item_name : vname + '',
					item_value : vvalue + '',
					item_value2 : vvalue2 + '',
				},
			success: function(res){
				$('#preview-loading').fadeOut();
				if(res.result){
					document.getElementById('preview_iframe').contentDocument.location.reload(true);
				}
			}
		});
	});
	
	//select box
	$(document).delegate('#edit-designation-line-2, #edit-website, #edit-main-image', 'change', function(){
		var vname = $(this).attr('name');
		var vvalue = $(this).find('option:selected').val();
		var vvalue2 = $('#edit-other').val();
		var vcache_id = $('input[name="cache_id"]').val();
		var vdivision = $('#edit-division').find('option:selected').val();
		
		
		$('#preview-loading').fadeIn();
		$.ajax({
			type: 'POST',
			url: Drupal.settings.basePath + 'admin/esignature/generator/item_ref',
			dataType: 'json',
			data: {
					division : vdivision + '', 
					cache_id : vcache_id + '',
					item_name : vname + '',
					item_value : vvalue + '',
					item_value2 : vvalue2 + '',
				},
			success: function(res){
				$('#preview-loading').fadeOut();
				if(res.result){
					document.getElementById('preview_iframe').contentDocument.location.reload(true);
				}
			}
		});	
	});
	
	//multiple image 
	$(document).delegate('#add-multi-bottom_image', 'click', function(){
		var obj = $($('#multi-bottom_image .multiple-item-field:first').clone());
		obj.find('select option:selected').removeAttr('selected');
		obj.appendTo('#multi-bottom_image');
	});
	//delete one image
	$(document).delegate('#multi-bottom_image .delete-item', 'click', function(){
		if($('.multiple-item-field').length > 1){
			$(this).parent().fadeOut('normal', function(){
				
				$(this).remove();
			
				var vcache_id = $('input[name="cache_id"]').val();
				var vdivision = $('#edit-division').find('option:selected').val();
				
				var vname = 'bottom_image';
				var vvalue = new Array();
				$('.item-bottom_image').each(function(){
					vvalue.push($(this).find('option:selected').val());
				});
				
				$('#preview-loading').fadeIn();
				$.ajax({
					type: 'POST',
					url: Drupal.settings.basePath + 'admin/esignature/generator/item_ref',
					dataType: 'json',
					data: {
							division : vdivision + '', 
							cache_id : vcache_id + '',
							item_name : vname + '',
							item_value : vvalue
						},
					success: function(res){
						$('#preview-loading').fadeOut();
						if(res.result){
							document.getElementById('preview_iframe').contentDocument.location.reload(true);
						}
					}
				});	
			});
		}
		return false;
	});
	//change one image
	$(document).delegate('.item-bottom_image', 'change', function(){
		var vcache_id = $('input[name="cache_id"]').val();
		var vdivision = $('#edit-division').find('option:selected').val();
		
		var vname = 'bottom_image';
		var vvalue = new Array();
		$('.item-bottom_image').each(function(){
			vvalue.push($(this).find('option:selected').val());
		});
		
		$('#preview-loading').fadeIn();
		$.ajax({
			type: 'POST',
			url: Drupal.settings.basePath + 'admin/esignature/generator/item_ref',
			dataType: 'json',
			data: {
					division : vdivision + '', 
					cache_id : vcache_id + '',
					item_name : vname + '',
					item_value : vvalue
				},
			success: function(res){
				$('#preview-loading').fadeOut();
				if(res.result){
					document.getElementById('preview_iframe').contentDocument.location.reload(true);
				}
			}
		});	
	});
	
	function showLoading(){
		$('#loading').fadeIn('slow');
	}
	
	function hideLoading(){
		$('#loading').fadeOut('slow');
	}	
	
	
	//upload image
	if($('#form_image_upload').size()){
		$('#form_image_upload').ajaxForm({
			dataType : 'json',
			target : '#images-uploaded',
			success : showResponse
		});
	}
	
	function showResponse(data, statusText, xhr, $form){
		if(data.result){
			$('#images-uploaded').append(data.content).hide().fadeIn('normal');
			$('#field_image_location').val('');
		}else{
			var msg = '';
			for(var i = 0; i < data['error'].length; i ++){
				msg = msg + '\n' + data['error'][i];
			}
			alert(msg);
		}
	}
	
	//delete image
	$(document).delegate('a.remove-image', 'click', function(){
		var obj = $(this);
		$.ajax({
			type: 'GET',
			url: $(this).attr('href'),
			dataType: 'json',
			success: function(res){
				if(res.result){
					obj.parent().fadeOut('normal', function(){
						obj.remove();
					});
				}else{
					var msg = '';
					for(var i = 0; i < data['error'].length; i ++){
						msg = msg + '\n' + data['error'][i];
					}
					alert(msg);
				}
			}
		});
		return false;
	});
	
	
	// init on start
	var hash = location.hash;
	hash = hash.replace('#', '');
	if(hash){
		//console.log("#edit-division option[value='"+ hash +"']");
		// $("#edit-division option[value='"+ hash +"']").attr('selected', 'selected');
		// division_changed();
    setTimeout(1000, function(){
        $("#edit-division").val( hash );
        division_changed();
      });
	}
	inited = true;
});