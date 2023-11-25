[% USE raw %]
[% USE Koha %]
[%- USE KohaPlugins -%]
[% USE Asset %]
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="generator" content="Koha [% Version | html %]" /> <!-- leave this for stats -->
<meta name="viewport" content="width=device-width, initial-scale=1" />
[% IF ( Koha.Preference('OpacMetaDescription') ) %]
    <meta name="description" content="[% Koha.Preference('OpacMetaDescription') | html %]" />
[% END %]
<link rel="shortcut icon" href="[% IF ( Koha.Preference('OpacFavicon') ) %][% Koha.Preference('OpacFavicon') | url %][% ELSE %][% interface | url %]/[% theme | url %]/images/favicon.ico[% END %]" type="image/x-icon" />

[% IF ( Koha.Preference('OPACBaseURL') ) %]
    <link rel="search" type="application/opensearchdescription+xml" href="[% Koha.Preference('OPACBaseURL') | url %]/cgi-bin/koha/opac-search.pl?format=opensearchdescription" title="Search [% LibraryNameTitle | html %]">
    <link rel="unapi-server" type="application/xml" title="unAPI" href="[% Koha.Preference('OPACBaseURL') | url %]/cgi-bin/koha/unapi" />
[% END %]
[% IF ( bidi ) %]
    [% Asset.css("lib/jquery/jquery-ui-rtl-1.12.1.min.css") | $raw %]
[% ELSE %]
    [% Asset.css("lib/jquery/jquery.ui.1.10.0.ie.css") | $raw %]
    [% Asset.css("lib/jquery/jquery-ui-1.10.0.custom.css") | $raw %]
[% END %]
[% FILTER collapse %]
    [% PROCESS cssinclude %]
[% END %]
<script>
    var Koha = {};
    function _(s) { return s } // dummy function for gettext
</script>
[% IF lang && lang != 'en' %]
    [% Asset.js(lang _ '/js/locale_data.js') | $raw %]
[% END %]
[% Asset.js('js/Gettext.js') | $raw %]
[% Asset.js('js/i18n.js') | $raw %]
[% PROCESS 'html_helpers.inc' %]
[% KohaPlugins.get_plugins_opac_head | $raw %]

<!-- Google Fonts -->
<link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Open+Sans:ital,wght@0,300;0,400;0,500;0,600;0,700;1,300;1,400;1,600;1,700&family=Poppins:ital,wght@0,300;0,400;0,500;0,600;0,700;1,300;1,400;1,500;1,600;1,700&family=Inter:ital,wght@0,300;0,400;0,500;0,600;0,700;1,300;1,400;1,500;1,600;1,700&display=swap" rel="stylesheet">
  <link href="https://fonts.googleapis.com/css2?family=Tiro+Bangla:ital@0;1&display=swap" rel="stylesheet">
  <!-- Vendor CSS Files -->
  [% Asset.css('assets/vendor/bootstrap/css/bootstrap.min.css') | $raw %]
  [% Asset.css('assets/vendor/bootstrap-icons/bootstrap-icons.css') | $raw %]
  [% Asset.css('assets/vendor/fontawesome-free/css/all.min.css') | $raw %]
  [% Asset.css('assets/vendor/glightbox/css/glightbox.min.css') | $raw %]
<!--  [% Asset.css('assets/vendor/swiper/swiper-bundle.min.css') | $raw %] -->
<!--  [% Asset.css('assets/vendor/aos/aos.css') | $raw %] -->

  <!-- Template Main CSS File -->
  [% Asset.css('assets/css/main.css') | $raw %]
  <!-- RAOWA Specific Color -->
  [% Asset.css('assets/css/raowa.css') | $raw %]