$(function() {
	var $dialogBox = $('#dialog_box');
	
	/* menu */
	$('#menu, #drop_menu').hover(function() {
		$('#drop_menu').show();
	},function(){
		$('#drop_menu').hide();
	});
	
	/* dialog_box */
	
	function showDialog(text, type) {
		$dialogBox.empty();
		$dialogBox.prepend('<p>' + text + '</p>');
		$('#dialog_bg').show();
		var $cancelButton = $('<a id="dialog_cancel">Cancel</a>');
		$cancelButton.click(function(e) {
			e.preventDefault();
			$('#dialog_bg').hide();
			$dialogBox.hide();
		});
		if(type == 'ok') {
			var $okButton = $('<a>OK</a>');
			$okButton.click(function() {
				/* ok button process */
				return false;
			});
			$dialogBox.append($okButton).append($cancelButton);
		} else {
			$dialogBox.append($cancelButton);
		}
		$dialogBox.show();
	}
	
	$('.option_delete').click(function(e) {
		e.preventDefault();
		showDialog('Are you sure you want to delete this?', 'ok');
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