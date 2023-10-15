[% IF ( listResults ) %]
                [% IF ( Koha.Preference('OpacBrowseResults') && busc ) %]
                    <div class="nav_results">
                        <div class="l_Results" style="display:none;">
                            [% IF ( listResults ) %]
                                <a href="#" id="a_listResults"><i class="fa fa-bars" aria-hidden="true"></i> Browse results</a>
                            [% ELSE %]
                                <span><i class="fa fa-bars" aria-hidden="true"></i> Browse results</span>
                            [% END %]
                            <a href="#" class="close_pagination"><i class="fa fa-remove" aria-hidden="true"></i> Close</a>
                        </div>
                        [% IF ( listResults ) %]
                            <div class="results-pagination">
                                    <ul class="list-group list-group-flush" id="ul_pagination_lists">
                                        [% FOREACH listitem IN listResults %]
                                            [% IF ( listitem.biblionumber == biblionumber ) %]
                                                <li class="list-group-item d-flex justify-content-between align-items-center" id="li_pag_[% loop.count | html %]" class="highlight" title="Go to detail">
                                                    <a href="opac-detail.pl?biblionumber=[% biblionumber | uri %]&amp;query_desc=[% query_desc |uri %]">[% title | html %]</a><br> [% IF ( author ) %]by [% author | html %][% END %]
                                                    <span class="badge bg-primary rounded-pill">[% loop.count  + offset | html %]</span>
                                                </li>
                                            [% ELSE %]
                                                <li class="list-group-item d-flex justify-content-between align-items-center" id="li_pag_[% loop.count | html %]" title="Go to detail">
                                                    <a href="opac-detail.pl?biblionumber=[% listitem.biblionumber | uri %]&amp;query_desc=[% query_desc |uri %]">[% listitem.title | html %]</a><br> [% IF ( listitem.author ) %]by [% listitem.author | html %][% END %]
                                                    <span class="badge bg-primary rounded-pill">[% loop.count  + offset | html %]</span>
                                                </li>
                                            [% END # /IF listitem.biblionumber %]
                                        [% END # /FOREACH listitem %]
                                    </ul> <!-- /#ul_pagination_list -->
                            </div> <!-- /.results-pagination -->
                        [% END # /IF ( listResults ) %]
                        <div class="pagination_footer">
                            <a href="#" class="close_pagination"><i class="fa fa-remove" aria-hidden="true"></i> Close</a>
                        </div>
                    </div> <!-- /.nav_results -->
                [% END # / IF OpacBrowseResults && busc %]
                <nav aria-label="Page navigation Results">
                    <ul id="listResults" class="pagination">
                        [% FOREACH listitem IN listResults %]
                            [% IF ( listitem.biblionumber == biblionumber ) %]
                                <li class="page-item li_pag_[% loop.count | html %] highlight">
                            [% ELSE %]
                                <li class="page-item li_pag_[% loop.count | html %]">
                            [% END %]
                                <a class="page-link" href="opac-detail.pl?biblionumber=[% listitem.biblionumber | uri %]&amp;query_desc=[% query_desc |uri %]" title="View record &quot;[% listitem.title | html %]&quot;" id="a_pag_[% loop.count | html %]">[% loop.count + offset | html %]</a>
                            </li>
                        [% END # /FOREACH listitem %]
                    </ul> <!-- /#listResults -->
                </nav>
            [% END %]