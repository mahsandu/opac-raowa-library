[% USE raw %]
[% USE Biblio %]
<ul id="action" class="list-group list-group-flush">
    [% UNLESS ( norequests ) %]
        [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
            [% IF Koha.Preference( 'OPACHoldRequests' ) == 1 %]
                [% IF ( ReservableItems ) %]
                    <li class="list-group-item list-group-item-action"><a class="reserve" href="/cgi-bin/koha/opac-reserve.pl?biblionumber=[% biblio.biblionumber | html %]"><i class="fa fa-fw fa-bookmark" aria-hidden="true"></i> Place hold</a></li>
                [% END %]
            [% END %]
        [% END %]
    [% END %]

    <li class="list-group-item list-group-item-action"><a class="print-large" href="#"><i class="fa fa-fw fa-print" aria-hidden="true"></i> Print</a></li>

    [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
        [% IF artreqpossible %]
            <li class="list-group-item list-group-item-action"><a class="article_request" href="/cgi-bin/koha/opac-request-article.pl?biblionumber=[% biblio.biblionumber | html %]"><i class="fa fa-fw fa-file-alt" aria-hidden="true"></i> Request article</a></li>
        [% END %]
    [% END %]

    [% IF Koha.Preference( 'virtualshelves' ) == 1 %]
        [% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && loggedinusername ) %]
            <li class="list-group-item list-group-item-action"><a class="addtoshelf" href="/cgi-bin/koha/opac-addbybiblionumber.pl?biblionumber=[% biblio.biblionumber | html %]"><i class="fa fa-list" aria-hidden="true"></i> Save to your lists</a></li>
        [% END %]
    [% END %]

    [% IF Koha.Preference( 'opacbookbag' ) == 1 %]
        [% IF ( incart ) %]
            <li class="list-group-item list-group-item-action"><a data-biblionumber="[% biblio.biblionumber | html %]" class="addtocart incart cart[% biblio.biblionumber | html %] addrecord btn-link btn-lg" href="#"><i class="fa  fa-shopping-cart" aria-hidden="true"></i> In your cart</a> <a data-biblionumber="[% biblio.biblionumber | html %]" class="cartRemove cartR[% biblio.biblionumber | html %]" href="#">(remove)</a></li>
        [% ELSE %]
            <li class="list-group-item list-group-item-action"><a data-biblionumber="[% biblio.biblionumber | html %]" class="cart[% biblio.biblionumber | html %] addrecord btn btn-link btn-lg" href="#"><i class="fa fa-shopping-cart" aria-hidden="true"></i> Add to your cart</a>  <a style="display:none;" data-biblionumber="[% biblio.biblionumber | html %]" class="cartRemove cartR[% biblio.biblionumber | html %]" href="#">(remove)</a></li>
        [% END %]
    [% END %]

    [% IF Koha.Preference('suggestion') %]
        <li class="list-group-item list-group-item-action"><a class="suggest_for_purchase" href="/cgi-bin/koha/opac-suggestions.pl?op=add&biblionumber=[% biblio.biblionumber | url %]"><i class="fa fa-fw fa-gift" aria-hidden="true"></i> Suggest for purchase</a></li>
    [% END %]

    [% IF ( OpacHighlightedWords && query_desc ) %]
    <li class="list-group-item list-group-item-action">
        <a href="#" class="highlight_toggle" id="highlight_toggle_off"><i class="fas fa-pencil-alt" aria-hidden="true"></i> Unhighlight</a>
        <a href="#" class="highlight_toggle" id="highlight_toggle_on"><i class="fas fa-marker" aria-hidden="true"></i> Highlight</a>
    </li>
    [% END %]


    [% IF ( Koha.Preference('OPACDetailQRCode' ) ) %]
        <li class="list-group-item list-group-item-action">
            <a class="show_qrcode" href="#"><i class="fa fa-fw fa-qrcode" aria-hidden="true"></i> Send to device</a>
            <div id="qrcode" class="d-none"></div>
        </li>
    [% END %]

    [% SET export_options = Koha.Preference('OpacExportOptions').split(',') %]
    [% IF export_options.size %]
        <li class="list-group-item list-group-item-action">
            <div id="export">
                <div class="dropdown">
                    <a id="format" class="dropdown-toggle" data-bs-toggle="dropdown" href="#"><i class="fa fa-fw fa-download" aria-hidden="true"></i> Save record <b class="caret"></b></a>
                    <ul class="dropdown-menu dropdown-menu-right" aria-labelledby="format">
                        [% FOREACH option IN export_options %]
                            [% IF option == 'dc' %]
                                <li>
                                <a class="dropdown-item" href="#" data-toggle="modal" data-target="#exportModal_">Dublin Core</a>
                                </li>
                            [% ELSE %]
                                <li>
                                    <a class="dropdown-item" href="/cgi-bin/koha/opac-export.pl?op=export&amp;bib=[% biblio.biblionumber | html %]&amp;format=[% option | html %]">
                                        [% SWITCH option %]
                                            [% CASE 'bibtex' %]BIBTEX
                                            [% CASE 'endnote' %]EndNote
                                            [% CASE 'marcxml' %]MARCXML
                                            [% CASE 'marc8' %]MARC (non-Unicode/MARC-8)
                                            [% CASE 'utf8' %]MARC (Unicode/UTF-8)
                                            [% CASE 'marcstd' %]MARC (Unicode/UTF-8, Standard)
                                            [% CASE 'mods' %]MODS (XML)
                                            [% CASE 'ris' %]RIS
                                            [% CASE 'isbd' %]ISBD
                                        [% END %]
                                    </a>
                                </li>
                            [% END %]
                        [% END %]
                    </ul> <!-- /.dropdown-menu -->
                </div> <!-- /.dropdown -->
            </div> <!-- /#export -->
        </li>
    [% END %]

    [% IF ( OPACSearchForTitleIn ) %]
        <li class="list-group-item">
            <div id="moresearches_menu">
                <div class="dropdown">
                    <a id="furthersearches" class="dropdown-toggle" data-bs-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
                        <i class="fa fa-fw fa-search" aria-hidden="true"></i> More searches
                    </a>
                    <ul class="dropdown-menu dropdown-menu-right" aria-labelledby="furthersearches">
                        <div class="dropdown-header">Search for this title in:</div>
                        <li>[% OPACSearchForTitleIn | $raw %]</li>
                    </ul>
                </div>
            </div>
        </li>
    [% END %]
</ul>

<!-- Dublin Core Modal Form -->
<div class="modal" id="exportModal_" tabindex="-1" role="dialog" aria-labelledby="exportModalLabel" aria-hidden="true">
    <div class="modal-dialog">
        <div class="modal-content">
            <div class="modal-header">
                <h3 class="modal-title" id="exportModalLabel">Exporting to Dublin Core...</h3>
                <button type="button" class="closebtn" data-dismiss="modal" aria-hidden="true">&times;</button>
            </div>
            <form method="get" action="/cgi-bin/koha/opac-export.pl">
                <div class="modal-body">
                    <fieldset id="dc_fieldset">
                        <input id="input-simple" type="radio" name="format" value="rdfdc">
                        <label class="label_dc" for="input-simple">Simple DC-RDF</label>
                        <br>
                        <input id="input-oai" type="radio" name="format" value="oaidc" checked>
                        <label class="label_dc" for="input-oai">OAI-DC</label>
                        <br>
                        <input id="input-srw" type="radio" name="format" value="srwdc">
                        <label class="label_dc" for="input-srw">SRW-DC</label>
                        <br>
                        <input type="hidden" name="op" value="export">
                        <input type="hidden" name="bib" value="[% biblio.biblionumber | html %]">
                    </fieldset>
                </div>
                <div class="modal-footer">
                    <button type="submit" class="btn btn-primary">Export</button>
                    <button class="btn btn-link btn-lg" data-dismiss="modal" aria-hidden="true">Cancel</button>
                </div>
            </form>
        </div> <!-- /.modal-content -->
    </div> <!-- /.modal-dialog -->
</div> <!-- /.modal -->
