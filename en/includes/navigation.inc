[% USE raw %]

[% IF IsPatronPage %]
    <div id="usermenu">[% INCLUDE usermenu.inc %]</div>
[% END %]

[% IF ( OpacNav ) %]
    [% PROCESS koha_news_block news => OpacNav %]
[% END %]

[% IF ( OpacNavBottom ) %]
    [% PROCESS koha_news_block news => OpacNavBottom %]
[% END %]
