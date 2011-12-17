<?php

/* test.html */
class __TwigTemplate_476dbe8be89303113105722353375184 extends Twig_Template
{
    protected function doGetParent(array $context)
    {
        return false;
    }

    protected function doDisplay(array $context, array $blocks = array())
    {
        $context = array_merge($this->env->getGlobals(), $context);

        // line 1
        echo "<html>
\t<head>
\t\t<title>";
        // line 3
        echo twig_escape_filter($this->env, $this->getContext($context, "pageTitle"), "html", null, true);
        echo "</title>
\t</head>
\t<body>Dit is een zin met een variabele: ";
        // line 5
        echo twig_escape_filter($this->env, $this->env->getExtension('SystemTwig')->translate("hello", $this->getContext($context, "username")), "html", null, true);
        echo "</body>
</html>";
    }

    public function getTemplateName()
    {
        return "test.html";
    }

    public function isTraitable()
    {
        return false;
    }
}
