{% assign pages = site.pages | sort_natural: "title" %}
{% for page in pages %}{% if page.categories contains include.name %}* [{{ page.title }}]({{ page.url | absolute_url }})
{% endif %}{% endfor %}