$(function() {
	
	/* menu */
	$('#menu, #drop_menu').hover(function() {
		$('#drop_menu').show();
	},function(){
		$('#drop_menu').hide();
	});
	
	/* dialog_box */
	$('#dialog_box a').click(function() {
		$('#dialog_box').hide();
		$('#dialog_bg').hide();
		$('#dialog_box p').empty();
	});
	
	function showDialog(text) {
		$('#dialog_box p').prepend(text);
		$('#dialog_bg').show();
		$('#dialog_box').show();
	}
	
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
					showDialog('you dumbass used the wrong username or password!');
				}
			}
		});
	});
});