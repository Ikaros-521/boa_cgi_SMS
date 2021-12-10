$(document).ready(function() {
	var colors=['#FF6666','#FF9900','#f9f900','#00dd0e','#98eeff','#5999ff','#cd77ff'];//颜色数组，可以随意增减
	i=0;
	setInterval(function () {//setInterval是每间隔一段时间执行一次的函数，下面设置的1000毫秒
	    var p = document.getElementById('bottom');
	    p.style.color=colors[i];
	    i++;//跳到下一个数组的值
	    i==7?i=0:i=i;//如果到数组末尾了又跳到第一个；
	}, 200);
});

// 失焦判空
function check_username() {
	var username = document.myform.username.value;
	var tip_username = document.getElementById("tip_username");
	if(username.length == 0)
	{
		tip_username.innerHTML = "请输入用户名";
		document.getElementById("username").style.borderColor = "#ff6158";
		tip_username.style.display="inline";
		return false;
	}
	else if(username.length<1 || username.length>20)
	{
		tip_username.innerHTML = "用户名为1-20位";
		document.getElementById("username").style.borderColor = "#ff6158";
		tip_username.style.display="inline";
		return false;
	}
	else
	{
		document.getElementById("username").style.borderColor = "#C4C6CF";
		tip_username.style.display="none";
		return true;
	}
}

function check_password() {
	var password = document.myform.password.value;
	var tip_password = document.getElementById("tip_password");
	if(password.length == 0)
	{
		tip_password.innerHTML = "请输入密码";
		document.getElementById("password").style.borderColor = "#ff6158";
		tip_password.style.display="inline";
		return false;   
	}
	if(password.length < 1 || password.length>20)
	{
		tip_password.innerHTML = "密码为1-20位";
		document.getElementById("password").style.borderColor = "#ff6158";
		tip_password.style.display="inline";
		return false;   
	}
	else
	{
		document.getElementById("password").style.borderColor = "#C4C6CF";
		tip_password.style.display="none";
		return true;
	}
}

function Base64() {  

	// private property  
	_keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";  

	// public method for encoding  
	this.encode = function (input) {  
		var output = "";  
		var chr1, chr2, chr3, enc1, enc2, enc3, enc4;  
		var i = 0;  
		input = _utf8_encode(input);  
		while (i < input.length) {  
			chr1 = input.charCodeAt(i++);  
			chr2 = input.charCodeAt(i++);  
			chr3 = input.charCodeAt(i++);  
			enc1 = chr1 >> 2;  
			enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);  
			enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);  
			enc4 = chr3 & 63;  
			if (isNaN(chr2)) {  
				enc3 = enc4 = 64;  
			} else if (isNaN(chr3)) {  
				enc4 = 64;  
			}  
			output = output +  
			_keyStr.charAt(enc1) + _keyStr.charAt(enc2) +  
			_keyStr.charAt(enc3) + _keyStr.charAt(enc4);  
		}  
		return output;  
	}  

	// public method for decoding  
	this.decode = function (input) {  
		var output = "";  
		var chr1, chr2, chr3;  
		var enc1, enc2, enc3, enc4;  
		var i = 0;  
		input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");  
		while (i < input.length) {  
			enc1 = _keyStr.indexOf(input.charAt(i++));  
			enc2 = _keyStr.indexOf(input.charAt(i++));  
			enc3 = _keyStr.indexOf(input.charAt(i++));  
			enc4 = _keyStr.indexOf(input.charAt(i++));  
			chr1 = (enc1 << 2) | (enc2 >> 4);  
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);  
			chr3 = ((enc3 & 3) << 6) | enc4;  
			output = output + String.fromCharCode(chr1);  
			if (enc3 != 64) {  
				output = output + String.fromCharCode(chr2);  
			}  
			if (enc4 != 64) {  
				output = output + String.fromCharCode(chr3);  
			}  
		}  
		output = _utf8_decode(output);  
		return output;  
	}  

	// private method for UTF-8 encoding  
	_utf8_encode = function (string) {  
		string = string.toString();
		string = string.replace(/\r\n/g,"\n");
		var utftext = "";  
		for (var n = 0; n < string.length; n++) {  
			var c = string.charCodeAt(n);  
			if (c < 128) {  
				utftext += String.fromCharCode(c);  
			} else if((c > 127) && (c < 2048)) {  
				utftext += String.fromCharCode((c >> 6) | 192);  
				utftext += String.fromCharCode((c & 63) | 128);  
			} else {  
				utftext += String.fromCharCode((c >> 12) | 224);  
				utftext += String.fromCharCode(((c >> 6) & 63) | 128);  
				utftext += String.fromCharCode((c & 63) | 128);  
			}  

		}  
		return utftext;  
	}  

	// private method for UTF-8 decoding  
	_utf8_decode = function (utftext) {  
		var string = "";  
		var i = 0;  
		var c = c1 = c2 = 0;  
		while ( i < utftext.length ) {  
			c = utftext.charCodeAt(i);  
			if (c < 128) {  
				string += String.fromCharCode(c);  
				i++;  
			} else if((c > 191) && (c < 224)) {  
				c2 = utftext.charCodeAt(i+1);  
				string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));  
				i += 2;  
			} else {  
				c2 = utftext.charCodeAt(i+1);  
				c3 = utftext.charCodeAt(i+2);  
				string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));  
				i += 3;  
			}  
		}  
		return string;  
	}  
}

function login() {
	if(check_username() && check_password())
	{
		var base = new Base64();
		var password = document.myform.password.value;
		var base_pwd = base.encode(password);
		document.myform.password.value = base_pwd;
		document.myform.submit();
		document.myform.password.value = password;
		return true;
	}
	else
	{
		return false;
	}
}