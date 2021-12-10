$(document).ready(function() {
	check_session();
	get_state();
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
				get_state();
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

// 回显配置运行状态
function get_state()
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
		if(xmlhttp.readyState==4)
		{
			if(xmlhttp.status==200)
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
				//alert(ret);
				if(ret.length == 0)
				{
					
				}
				else
				{
					if(ret.indexOf("error") != -1)
					{
						alert(ret);
					}
					else
					{
						$("#state").html(ret);
						if(ret.indexOf("active") != -1) document.getElementById("state").style.color="#AEDD81";
						if(ret.indexOf("inactive") != -1) document.getElementById("state").style.color="#D0D0D0";
						if(ret.indexOf("failed") != -1) document.getElementById("state").style.color="#D24D57";
					}
				}
			}
			else
			{
				//alert(xmlhttp.status);
			}

		}
		else
		{
			//alert(xmlhttp.readyState);
		}
	}
	
	xmlhttp.open("GET","cgi-bin/get_squid_state.cgi?get",true);
	xmlhttp.send();
}

// alert结果
function alert_ret(ret)
{
    if(ret == "success")
    {
        alert("执行成功");
    }
    else if(ret == "failed")
    {
        alert("执行失败");
    }
}

// 设置MySQL
function set_squid(func)
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
		if(xmlhttp.readyState==4)
		{
			if(xmlhttp.status==200)
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
					alert_ret(ret);
				}
				get_state();
			}
			else
			{
				//alert(xmlhttp.status);
			}

		}
		else
		{
			//alert(xmlhttp.readyState);
		}
	}
	xmlhttp.open("GET","cgi-bin/set_squid.cgi?" + func,true);
	xmlhttp.send();
}