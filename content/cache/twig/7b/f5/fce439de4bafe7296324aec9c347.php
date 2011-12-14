<?php

/* test.html */
class __TwigTemplate_7bf5fce439de4bafe7296324aec9c347 extends Twig_Template
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
        echo strtr(gettext("%pageTitle%"), array("%pageTitle%" => $this->getContext($context, "pageTitle"), ));
        // line 5
        echo "</title>
\t</head>
\t<body>Dit is een zin met een variabele: ";
        // line 7
        echo twig_escape_filter($this->env, Array($this->getContext($context, "hello")), "html", null, true);
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
