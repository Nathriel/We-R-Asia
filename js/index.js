$(function() {
	
	/* menu */
	$('#menu, #drop_menu').hover(function() {
		$('#drop_menu').show();
	},function(){
		$('#drop_menu').hide();
	});
	
	/* dialog_box */
	
	function showDialog(text, type) {
		$('#dialog_box').prepend('<p>' + text + '</p>');
		$('#dialog_bg').show();
		if(type == 'ok') {
			$('#dialog_box').append('<a id="dialog_ok">OK</a><a id="dialog_cancel">Cancel</a>');
		} else {
			$('#dialog_box').append('<a id="dialog_cancel">Cancel</a>');
		}
		$('#dialog_box').show();
		
		$('#dialog_box #dialog_ok').click(function() {
			/* ok button process */
			return false;
		});
		
		$('#dialog_box #dialog_cancel').click(function() {
			$('#dialog_box').hide();
			$('#dialog_bg').hide();
			$('#dialog_box').empty();
			return false;
		});
	}
	
	$('.option_delete').click(function(){
		showDialog('Are you sure you want to delete this?', 'ok');
		return false;
	});
	
	/* login */
	$('#loginForm').submit(function(e) {
		e.preventDefault();
		var username = $('#loginForm input[name="username"]').val();
		var passwordEncoded = sha256_digest($('#loginForm input[name="password"]').val());
		$.ajax({
			'url': $(this).attr('action'),
			'data': {
				'username': username,
				'password': passwordEncoded
			},
			'type': 'POST',
			'success': function(data) {
				if (data == 1) {
					// successful login!
                    //window.location='';
                    var url = window.location;
                    window.location = url + 'projects'
				} else {
					// you dumbass used the wrong username or password!
					showDialog('You dumbass used the wrong username or password!', 'cancel');
				}
			}
		});
	});
});