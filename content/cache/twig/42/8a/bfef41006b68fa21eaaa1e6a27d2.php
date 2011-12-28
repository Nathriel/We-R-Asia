<?php

/* login.html */
class __TwigTemplate_428abfef41006b68fa21eaaa1e6a27d2 extends Twig_Template
{
    protected function doGetParent(array $context)
    {
        return false;
    }

    protected function doDisplay(array $context, array $blocks = array())
    {
        $context = array_merge($this->env->getGlobals(), $context);

        // line 1
        echo "</doctype html>
<html>
\t<head>
\t\t<title>We R Asia &bull; Login</title>
\t\t<link rel=\"stylesheet\" media=\"screen\" href=\"./css/login_styles.css\">
\t</head>
\t<body>
\t\t<a href=\"#\" id=\"logo\">WE <span style=\"color: C00;\">R</span> <span style=\"color: black;\">ASIA</span></a>
\t\t
\t\t<br />
\t\t
\t\t<ul id=\"language_select\">
\t\t\t<li><a href=\"#\">English</a></li>
\t\t\t<li><a href=\"#\">Nederlands</a></li>
\t\t</ul>
\t\t
\t\t<br />
\t\t
\t\t<div id=\"loginbox\">
\t\t\t<form method=\"post\" action=\"#\">
\t\t\t\t<input type=\"text\" name=\"username\" placeholder=\"Username\"/>
\t\t\t\t<input type=\"password\" name=\"password\" placeholder=\"Password\"/>
\t\t\t\t<input type=\"submit\" name=\"submit\" value=\"Log in\"/>
\t\t\t</form>
\t\t\t<a href=\"#\" class=\"forget\">Forgot your password?</a>
\t\t</div>
\t</body>
</html>";
    }

    public function getTemplateName()
    {
        return "login.html";
    }

    public function isTraitable()
    {
        return true;
    }
}
