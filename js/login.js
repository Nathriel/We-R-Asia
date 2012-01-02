$(function() {
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
					alert('successful login!');
                    //window.location='';
                    var url = window.location;
                    window.location = url + 'projects'
				} else {
					// you dumbass used the wrong username or password!
					alert('you dumbass used the wrong username or password!');
				}
			}
		});
	});
});