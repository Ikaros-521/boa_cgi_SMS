$(document).ready(function() {
	check_session();
	
	var iframe = document.getElementById("iframe1"); 
	$('#link1').click(function() {
		window.location.href = 'index.html';
	});
	$('#link2').click(function() {
		iframe.src = "system_state.html";
	});
	$('#link3').click(function() {
		iframe.src = "system_log.html";
	});
	$('#link4').click(function() {
		iframe.src = "user_management.html";
	});
	$('#link5').click(function() {
		iframe.src = "mysql.html";
	});
	$('#link7').click(function() {
		logout();
	});
	$('#link8').click(function() {
		iframe.src = "cloud_resources.html";
	});
	$('#link9').click(function() {
		iframe.src = "apache.html";
	});
	$('#link10').click(function() {
		iframe.src = "squid.html";
	});
	$('#link11').click(function() {
		iframe.src = "deny_ping.html";
	});
	$('#link12').click(function() {
		iframe.src = "gateone.html";
	});
	$('#link13').click(function() {
		iframe.src = "log_management.html";
	});
	$('#link14').click(function() {
		iframe.src = "frp.html";
	});
	$('#link15').click(function() {
		iframe.src = "about.html";
	});
	
	var colors=['#FF6666','#FF9900','#f9f900','#00dd0e','#98eeff','#5999ff','#cd77ff'];//颜色数组，可以随意增减
	i=0;
	setInterval(function () {//setInterval是每间隔一段时间执行一次的函数，下面设置的1000毫秒
	    var p = document.getElementById('bottom');
	    p.style.color=colors[i];
	    i++;//跳到下一个数组的值
	    i==7?i=0:i=i;//如果到数组末尾了又跳到第一个；
	}, 200);
	
	console.log('\
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@@@.:;;;++;;;;:,@@@@@@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@@:;+++++;;++++;;;.@@@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@:++++;;;;;;;;;;+++;,@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@.;+++;;;;;;;;;;;;;;++;:@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@;+++;;;;;;;;;;;;;;;;;;++;:@@@@@@@@@@@@@@\n\
	@@@@@@@@@:+++;;;;;;;;;;;;;;;;;;;;++;.@@@@@@@@@@@@@\n\
	@@@@@@@@;;+;;;;;;;;;;;;;;;;;;;;;;;++:@@@@@@@@@@@@@\n\
	@@@@@@@@;+;;;;:::;;;;;;;;;;;;;;;;:;+;,@@@@@@@@@@@@\n\
	@@@@@@@:+;;:;;:::;:;;:;;;;::;;:;:::;+;.@@@@@@@@@@@\n\
	@@@@@@.;+;::;:,:;:;;+:++:;:::+;:::::++:+@@@@@@@@@@\n\
	@@@@@@:+;;:;;:::;;;+%;*?;;:,:;*;;;;:;+;:@@@@@@@@@@\n\
	@@@@@@;;;+;;+;:;;;+??;*?++;,:;+++;;;:++:@@@@@@@@@@\n\
	@@@@@.++*+;;+;;;;+?;?**??+;:;;+.:+;;;;+;;@@@@@@@@@\n\
	@@@@@,+;;;;*++*;+?+;**;:?*;;;;*:,+;;;;+;,@@@@@@@@@\n\
	@@@@@,:,+;+?+?++?+;,?#%*??+;;;*;;:+;;;;+:@@@@@@@@@\n\
	@@@@@@@:+;*?+?#%;;,,?###@#+;;;*;;,+;;;;+:@@@@@@@@@\n\
	@@@@@@@;+;??+%#%;,,,;SSS#S*+++*;..:+;?;+;@@@@@@@@@\n\
	@@@@@@@:+**?*?SS,,,,,S#S#+***?*;..;?;**+;@@@@@@@@@\n\
	@@@@@@@:+*??*??S,,,,,*%SS+???%++;***;+;;;.@@@@@@@@\n\
	@@@@@@@:*?*;*+;%:,,,,;?S?+%%%S?%+,:?;+:,,,@@@@@@@@\n\
	@@@@@@@,*?,;+;+S:,,,,%%?+;S%S%++:+??+:,,,:@@@@@@@@\n\
	@@@@@@@,:,@;::;+,,,,,+?%*+S%#?*???*;,,,,,.@@@@@@@@\n\
	@@@@@@@@:;,::;;:,,,,,,,,,?SS#??*?+,.,,,:,@@@@@@@@@\n\
	@@@@@@;;+;;+:,:%?%%*;,,,,SS#%*??%,.,,,,,:@@@@@@@@@\n\
	@@@@@.+++,++:;???%S?%%;.+#####??;.,,,,,,:@@@@@@@@@\n\
	@@@@@:++::??+S#??%#??S%?#@#S*+?*,,,,,,:,@@@@@@@@@@\n\
	@@@@@:;;:*?;+%#%?S#??%SS%+#%..;+:,,,,,,@@@@@@@@@@@\n\
	@@@@@@,,*S*;?SS?%##%?S#?,.:#+,,+:,,,,,,@@@@@@@@@@@\n\
	@@@@@@@;%%?%#%?*S##??##?,..*#,,+:,,;*;.@@@@@@@@@@@\n\
	@@@@@@.*%??#S*?S#@###%;:*,.:#:,+;:;*+:@@@@@@@@@@@@\n\
	@@@@@@,%S??SS%##@@#%S+..;;.,#*;???*?+++:@@@@@@@@@@\n\
	@@@@@@:S%??%####@@S,,*,.;*;+#*;+?%??#S%+.@@@@@@@@@\n\
	@@@@@@:%???%@###@@?,,:**S##S*;.,%S?;+*?+.,..@@@@@@\n\
	@@@@@@;%??%#@###@@#:.;@@#@%%%,.,%S*;++*++++;.@@@@@\n\
	@@@@@@,%S?S@@###@@@%+#@@#@?;,.:?;??++?%?***+.@@@@@\n\
	@@@@@@.*S?S####@@####@@##@?..:*,+:??**%+;;;;..@@@@\n\
	@@@@@@:+%?%####@@####@@#@%;:.;;:,+;?**;++;,:;:,@@@\n\
	@@@@@@;;*%?%@##@@@###@#S#*:;*+,;.+***?******+:.@@@\n\
	@@@@@@:;:??%@###%##@#%++;+*:+;,:;+%?*;+++++;:.@@@@\n\
	@@@@@@.+;:?%@@#%;+S*;;,:::**+,;:%??*+.@....@@@@@@@\n\
	@@@@@@@;*::?#S#S+;,..,:,;:?+?++*%?+::@@@@@@@@@@@@@\n\
	@@@@@@@.+*+++?%S++...,;:***??+;++:.@@@@@@@@@@@@@@@\n\
	@@@@@@@@:::..,;+*+;;+*?**+;;;+;:.@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@@@,+*++;;:,..@@@@@@@@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@@@@::,.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
	');

	console.log('\n\
	___ _                       \n\
	|_ _| | ____ _ _ __ ___  ___ \n\
	 | || |/ / _` | \'__/ _ \\/ __|\n\
	 | ||   < (_| | | | (_) \\__ \\\n\
	|___|_|\\_\\__,_|_|  \\___/|___/\n\
	\n\
	\n\
	');
	
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
					jump_to_login();
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

function jump_to_login()
{
	window.location.href="login.html";
}

// 退出
function logout() {
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
				
			}
			else
			{
				if(ret.indexOf("error") != -1)
				{
					my_alert(ret);
				}
				else if(ret.indexOf("success") != -1)
				{
					sessionStorage.clear();
					window.location.href="login.html";
				}
			}
		}
	}
	var username = sessionStorage.getItem('username');
	var session_id = sessionStorage.getItem('session_id');
	xmlhttp.open("GET","cgi-bin/logout.cgi?logout,username:"+username+",session_id:"+session_id+",",true);
	xmlhttp.send();
}