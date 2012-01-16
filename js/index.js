var baseHref;
function setBaseHref(a) {
	baseHref = a;
}

$(function() {
	var $dialogBox = $('#dialog_box');
	
	/* menu */
	$('#menu, #drop_menu').hover(function() {
		$('#drop_menu').show();
	},function(){
		$('#drop_menu').hide();
	});
	
    
    
	/* dialog_box */
	function showDialog(text, type, origin) {
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
				var url = window.location;
				var splitOrigin = $(origin).attr('href').split('/');
				var identifier = splitOrigin[0];
				if (identifier == 'project') {
					window.location = baseHref + 'projects/deleteProjectProcess/' + splitOrigin[1];
				} else if (identifier == 'product') {
					window.location = baseHref + 'projects/deleteProductProcess/' + splitOrigin[1];
				} else if(identifier == 'archive') {
					window.location = baseHref + 'projects/archiveProjectProcess/' + splitOrigin[1];
				} else if(identifier == 'document') {
					window.location = baseHref + 'projects/deleteDocumentProcess/' + splitOrigin[1];
				} else if(identifier == 'invoice') {
					window.location = baseHref + 'projects/deleteInvoiceProcess/' + splitOrigin[1];
				}
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
		showDialog('Are you sure you want to delete this?', 'ok', this);
	});
	
    /* password form */
    $('.passwordForm').submit(function(e)
    {
        //e.preventDefault();
        var password = $('.passwordForm input[name="password"]').val();
        var password_again = $('.passwordForm input[name="password_again"]').val();
        
        if(password && password == password_again){
            return true;
        }
        else
        {
            alert('The passwords are not equal');
            return false;
        }
    });
    
	$('.option_archive').click(function(e) {
		e.preventDefault();
		showDialog('Are you sure you want to archive this project?', 'ok', this);
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
					var conf = {
							frequency: 5000,
							spread: 5,
							duration: 500
					};
					
					$('#loginbox').vibrate(conf);
					$('#login_messagebox').show();
				}
			}
		});
	});
});

jQuery.fn.vibrate = function(conf) {
    var config = jQuery.extend({
            speed: 30, 
            duration: 2000, 
            frequency: 10000, 
            spread: 3
    }, conf);

    return this.each(function() {
            var t = jQuery(this);

            var vibrate = function() {
                    var topPos = Math.floor(Math.random() * config.spread) - ((config.spread - 1) / 2);
                    var leftPos = Math.floor(Math.random() * config.spread) - ((config.spread - 1) / 2);
                    var rotate = Math.floor(Math.random() * config.spread - (config.spread - 1) / 2);
                    t.css({position: 'relative', left: leftPos +'px', top: topPos +'px', WebkitTransform: 'rotate(' +rotate +'deg)'});
            };

            var doVibration = function () {
                    
					var vibrationInterval = setInterval(vibrate, config.speed);

                    var stopVibration = function() {
                            clearInterval(vibrationInterval);
                            t.css({position: 'static'});
                    };

                    setTimeout(stopVibration, config.duration);
            };
			
			doVibration();
    });
};

$(document).ready(function() {

	if(!Modernizr.input.placeholder){
		
		$("input").each(function(){
			if($(this).val()=="" && $(this).attr("placeholder")!="")
			{
				$(this).val($(this).attr("placeholder"));
	
				$(this).focus(function(){
					if($(this).val()==$(this).attr("placeholder")) $(this).val("");
				});
			
				$(this).blur(function(){
					if($(this).val()=="") $(this).val($(this).attr("placeholder"));
			
				});
			}
		});

	}
});