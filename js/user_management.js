$(document).ready(function() {
	check_session();
	get_username();
});

// check session
function check_session() {
	//$.alertable.alert('You Clicked OK');
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入str
			var str = xmlhttp.responseText;
			if(str.length == 0)
			{
				return;
			}
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var ret = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(ret.length == 0)
			{
				//my_alert(ret);
			}
			else
			{
				if(ret.indexOf("error") != -1)
				{
					my_alert(ret);
				}
				else if(ret.indexOf("failed") != -1)
				{
					sessionStorage.clear();
					window.parent.jump_to_login();
				}
				else if(ret.indexOf("success") != -1)
				{
				
				}
			}
			
			//alert("json:"+jsonstr);
			// 将jsonstr转换为json对象 json
		}
	}
	var sec = sessionStorage.getItem('sec');
	var session_id = sessionStorage.getItem('session_id');
	xmlhttp.open("GET","cgi-bin/check_session.cgi?check,sec:"+sec+",session_id:"+session_id+",",true);
	xmlhttp.send();
}

function check_username (){
	var cur_username = document.getElementById("cur_username"); 
	var new_username = document.getElementById("new_username"); 
	
	var new_tip = document.getElementById("username_tip");
	
	if(!check_empty_username())
	{
		return false;
	}

	//var form = document.getElementById("form1"); 
	//form.submit();
	
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入jsonstr
			var str = xmlhttp.responseText;
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var str = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(str.length == 0)
			{
				alert("收到错误信息");
			}
			else if(str.indexOf("error") != -1)
			{
				alert(str);
			}
			else if(str.indexOf("success") != -1)
			{
				alert("保存成功");
				get_username();
			}
			else
			{
				alert(str);
			}
		}
	}
	xmlhttp.open("GET","cgi-bin/change_username.cgi?set_username,new:" + new_username.value + ",",true);
	xmlhttp.send();
	
	return true;
}

// 帐号判空
function check_empty_username() {
	var new_username = document.getElementById("new_username"); 
	var new_tip = document.getElementById("username_tip");
	
	if(new_username.value == "")
	{
		new_tip.innerHTML = "请填写新用户名";
		new_tip.style.display="inline";
		new_username.style.borderColor = "#ff6158";
		return false;
	}
	else
	{
		if(new_username.value.length < 1 || new_username.value.length > 20)
		{
			//window.parent.show_save_tip("failed");
			new_tip.innerHTML = "用户名为1-20位";
			new_tip.style.display = "inline";
			new_username.style.borderColor = "#ff6158";
			return false;
		}

		new_tip.style.display="none";
		new_username.style.borderColor = "#C4C6CF";
		return true;
	}
}

// 密码判空
function check_empty_cur_password() {
	var apass = document.getElementById("cur_password"); 
	var cur_tip = document.getElementById("cur_password_tip"); 

	if(apass.value == "")
	{
		cur_tip.style.display="inline";
		apass.style.borderColor = "#ff6158";
		return false;
	}
	else
	{
		cur_tip.style.display="none";
		apass.style.borderColor = "#C4C6CF";
		return true;
	}
}

// 密码等级：至少包含字母、大小写数字、字符中的两种
function passwordLevel(password) {
	var Modes = 0;
	for (i = 0; i < password.length; i++) {
		Modes |= CharMode(password.charCodeAt(i));
	}
	return bitTotal(Modes);
	
	//CharMode函数
	function CharMode(iN) {
		if (iN >= 48 && iN <= 57)//数字
			return 1;
		if (iN >= 65 && iN <= 90) //大写字母
			return 2;
		if ((iN >= 97 && iN <= 122) || (iN >= 65 && iN <= 90)) //大小写
			return 4;
		else
			return 8; //特殊字符
	}

	//bitTotal函数
	function bitTotal(num) {
		modes = 0;
		for (i = 0; i < 4; i++) {
			if (num & 1) modes++;
			num >>>= 1;
		}
		return modes;
	}
}

function check_empty_new_password() { 
	var bpass = document.getElementById("new_password"); 
	var new_tip = document.getElementById("new_password_tip"); 
	
	if(bpass.value == "")
	{
		new_tip.innerHTML = "请填写新密码";
		new_tip.style.display="inline";
		bpass.style.borderColor = "#ff6158";
		return false;
	}
	else
	{
		if(bpass.value.length < 1 || bpass.value.length > 20)
		{
			new_tip.innerHTML = "新密码为1-20位";
			new_tip.style.display="inline";
			bpass.style.borderColor = "#ff6158";
			return false;
		}
		/*
		if(passwordLevel(bpass.value) < 2)
		{
			new_tip.innerHTML = "新密码至少包含字母、数字和特殊字符中的两种";
			new_tip.style.display="inline";
			bpass.style.borderColor = "#ff6158";
			return false;
		}
		*/
		
		new_tip.style.display="none";
		bpass.style.borderColor = "#C4C6CF";
		
		return true;
	}
}

function check_empty_new_password2() {
	var cpass = document.getElementById("new_password2");
	var new2_tip = document.getElementById("new_password2_tip"); 
	
	if(cpass.value == "")
	{
		new2_tip.style.display="inline";
		cpass.style.borderColor = "#ff6158";
		return false;
	}
	else
	{
		if(cpass.value.length < 1 || cpass.value.length > 20)
		{
			new2_tip.innerHTML = "确认新密码为1-20位";
			new2_tip.style.display="inline";
			cpass.style.borderColor = "#ff6158";
			return false;
		}
		/*
		if(passwordLevel(cpass.value) < 2)
		{
			new2_tip.innerHTML = "确认新密码至少包含字母、数字和特殊字符中的两种";
			new2_tip.style.display="inline";
			cpass.style.borderColor = "#ff6158";
			return false;
		}
		*/
		
		new2_tip.style.display="none";
		cpass.style.borderColor = "#C4C6CF";
		return true;
	}
}

function check_password (){
	var ret1 = check_empty_cur_password();
	var ret2 = check_empty_new_password();
	var ret3 = check_empty_new_password2();
	if(ret1 == true && ret2 == true && ret3 == true)
	{
	}
	else
	{
		return false;
	}
	
	var apass = document.getElementById("cur_password");
	var bpass = document.getElementById("new_password");
	var cpass = document.getElementById("new_password2");
	var cur_tip = document.getElementById("cur_password_tip");
	var new_tip = document.getElementById("new_password_tip");
	var new2_tip = document.getElementById("new_password2_tip");
	
	if(apass.value == bpass.value)
	{
		alert("新密码不能与当前密码相同，请重新输入");
		return false;
	}
	if(bpass.value != cpass.value)
	{
		alert("新密码与确认新密码不一致，请重新输入");
		return false;
	}
	
	//var form = document.getElementById("form2"); 
	//form.submit();
	
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入jsonstr
			var str = xmlhttp.responseText;
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var str = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(str.length == 0)
			{
				alert("收到错误信息");
			}
			else if(str.indexOf("error") != -1)
			{
				if(str.indexOf("cur_password") != -1)
				{
					alert("原密码错误！");
				}
				else
				{
					alert(str);
				}
			}
			else if(str.indexOf("success") != -1)
			{
				alert("保存成功");
			}
			else
			{
				alert(str);
			}
		}
	}
	xmlhttp.open("GET","cgi-bin/change_password.cgi?set_password,cur:"+ apass.value +",new:" + bpass.value + ",new2:"+ cpass.value +",",true);
	xmlhttp.send();
	
	return true;
}

function clean_user() {
	document.getElementById("cur_username").value = "";
	document.getElementById("new_username").value = "";
}

function clean_pass() {
	document.getElementById("cur_password").value = "";
	document.getElementById("new_password").value = "";
	document.getElementById("new_password2").value = "";
}


// 获取用户名
function get_username()
{
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入str
			var str = xmlhttp.responseText;
			if(str.length == 0)
			{
				return;
			}
			//alert(str);
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var username = xmlDoc.getElementsByTagName('p')[0].textContent;
			// 赋值给对应input
			if(username.indexOf("用户信息文件错误") == -1)
			{
				document.getElementById("cur_username").value = username;
			}
			else
			{
				alert("用户信息文件错误，请联系技术人员维护");
			}

		}
	}
	xmlhttp.open("GET","cgi-bin/get_username.cgi?get_username",true);
	xmlhttp.send();
};
