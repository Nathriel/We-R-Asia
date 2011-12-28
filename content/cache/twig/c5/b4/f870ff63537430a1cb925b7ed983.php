<?php

/* error.html */
class __TwigTemplate_c5b4f870ff63537430a1cb925b7ed983 extends Twig_Template
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
\t\t<style type=\"text/css\">
\t\t*::selection {
\t\t\tcolor: #FFF;
\t\t\tbackground-color: #00F;
\t\t}
\t\t#console {
\t\t\tfont-family: Andale Mono, Monaco, Courier New;
\t\t\tfont-size: 15px;
\t\t\tcolor: #0F0;
\t\t\tbackground-color: #000;
\t\t\tcursor: text;
\t\t\twidth: 80%;
\t\t\tmargin: auto;
\t\t\tborder: 1px solid #FFF;
\t\t}

\t\t#console p {
\t\t\tmin-height: 17px;
\t\t\tline-height: 17px;
\t\t\tmargin: 0 0 5 0;
\t\t\tposition: static;
\t\t}

\t\t.contains_sub {
\t\t\tmin-height: 0px;
\t\t}

\t\t.contains_sub :nth-child(1) {
\t\t\tmargin-top: 15px;
\t\t}

\t\t.contains_sub :last-child {
\t\t\tmargin-bottom: 15px;
\t\t}

\t\t.sub{
\t\t\tdisplay: block;
\t\t\tmargin-left: 50px;
\t\t}

\t\t.help_command {
\t\t\tmargin-right: 100px
\t\t}

\t\t#cursor {
\t\t\tdisplay: inline-block;
\t\t\twidth: 8px;
\t\t\theight: 14px;
\t\t\tbackground-color: #0F0;
\t\t\tposition: relative;
\t\t\tbottom: -2px;
\t\t}
\t\t
\t\t.command_line:before {
\t\t\tcontent: \"we-r-asia-server:~ we-r-asia-user\$ \";
\t\t}
\t\t</style>
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
\t<div id=\"console\">
\t\t<p>Last visit: **insert_cookie_date**</p>
\t\t<p>Type '?' or /help for options</p>
\t\t<p class=\"command_line\">help</p>
\t\t<p></p>
\t\t<p>WERASIA cli, version 0.1.3-dev (***insert_user_agent_here***)</p>
\t\t<p>This version of the cli has virtually no real functionality and none may possible be implemented in the future.</p>
\t\t<p>Please donate to the WERASIA cli project to supports its developers.</p>
\t\t<p>These shell commands are defined internally. Type `help` to see this list.</p>
\t\t<p class=\"contains_sub\">
\t\t\t<span class=\"sub\"><span class=\"help_command\">make [food]</span> Makes your favorite food.</span>
\t\t</p>
\t\t<p class=\"command_line\">make sandwich</p>
\t\t<p>Fuck you</p>
\t\t<p class=\"command_line\">sudo make sandwich</p>
\t\t<p>Ok.</p>
\t\t<p class=\"command_line\">get ***insert_page_url***</p>
\t\t<p>Error 404: Page not found</p>
\t\t<p class=\"command_line\"><span id=\"cursor\"></span></p>
\t\t<script type=\"text/javascript\">
\t\t\tvar cursorState = 1
\t\t\twindow.setInterval('toggleCursor()', 800);
\t\t\tfunction toggleCursor()
\t\t\t{
\t\t\t\tvar cursor = document.getElementById('cursor');
\t\t\t\tif(cursor != null)
\t\t\t\t{
\t\t\t\t\tif(window.cursorState == 1)
\t\t\t\t\t{
\t\t\t\t\t\tdocument.getElementById('cursor').style.display = 'none';
\t\t\t\t\t\twindow. cursorState = 0;
\t\t\t\t\t\tconsole.log(document.getElementById('cursor').style.backgroundColor);
\t\t\t\t\t}
\t\t\t\t\telse if (window.cursorState == 0)
\t\t\t\t\t{
\t\t\t\t\t\tdocument.getElementById('cursor').style.display = 'inline-block';
\t\t\t\t\t\twindow. cursorState = 1;
\t\t\t\t\t\tconsole.log(document.getElementById('cursor').style.backgroundColor);
\t\t\t\t\t}
\t\t\t\t}

\t\t\t}
\t\t</script>
\t</div>
\t</body>
</html>";
    }

    public function getTemplateName()
    {
        return "error.html";
    }

    public function isTraitable()
    {
        return true;
    }
}
