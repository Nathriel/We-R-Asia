$(function() {
	$('#file_upload').click(function(){
		$('#file_input').click();
	});
	
	$('#file_input').change(function(){
		$('#file_upload').val($('#file_input').val().replace(/C:\\fakepath\\/i, ''));
	});
});