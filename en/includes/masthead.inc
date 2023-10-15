[% USE raw %]
[% USE Koha %]
[% USE Branches %]
[% USE Categories %]
[% USE AdditionalContents %]
[% PROCESS 'html_helpers.inc' %]
[% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
[% SET OpacHeader = AdditionalContents.get( location => "opacheader", lang => lang, library => logged_in_user.branchcode, blocktitle => 0 ) %]
[% SET OpacCustomSearch = AdditionalContents.get( location => "OpacCustomSearch", lang => lang, library => logged_in_user.branchcode, blocktitle => 0 ) %]
[% SET OpacLoginInstructions = AdditionalContents.get( location => "OpacLoginInstructions", lang => lang, library => branchcode ) %]

<!-- ======= Header ======= -->
<header id="header bg-danger text-light" class="d-flex align-items-center aos-init aos-animate" data-aos="fade-down">

<div class="container">

    <div class="d-flex flex-row align-items-center">

        <div class="me-auto">
            <a class="navbar-brand text-capitalize float-left site-logo logo-png" href="/cgi-bin/koha/opac-main.pl" rel="home">
            
            [% IF ( LibraryNameTitle ) %]
            <span class="text-danger">
            <img src="/opac-tmpl/OPAC-RAOWA/assets/img/raowa-library.png" alt="[% LibraryNameTitle | html %]" class="brand-image w-auto h-10" height="50"> 
            </span>
            [% ELSE %]
                            <div class="text-danger">Library OPAC</div>
            [% END %]
            </a>
        </div> 
        <div class="me-0">
        
            <a class="text-danger" href="http://raowa.org"><i class="fas fa-globe" aria-hidden="true"></i> &nbsp; Raowa Website  &nbsp;</a>                
            [% IF loggedinusername %]
            <a class="text-danger" href="/cgi-bin/koha/opac-user.pl" ><i class="fas fa-user" aria-hidden="true"></i> &nbsp; My Account </a>
            <a class="logout text-danger" href="/cgi-bin/koha/opac-main.pl?logout.x=1"><i class="fas fa-sign-out-alt" aria-hidden="true"></i>&nbsp; Log out</a>
            [% ELSE %]
            <a class="text-danger" href="/cgi-bin/koha/opac-user.pl" ><i class="fas fa-user" aria-hidden="true"></i> &nbsp; Library Login </a>
            [% IF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
            <a href="/cgi-bin/koha/svc/auth/googleopenidconnect" class="text-danger" id="openid_connect" data-bs-toggle="tooltip" title="Login with RAOWA Email"><i class="fab fa-google text-iub-yellow"></i> &nbsp; Log in</a>
            [% END # /IF GoogleOpenIDConnect %]
            [% END %]
        </div>
    </div> <!-- end row -->
</div>
</header><!-- End Header -->
<!-- topbar close -->
        [% IF ( OpacHeader ) %]
            <div class="container-fluid">
                <div class="row">
                    <div class="col">
                        [% PROCESS koha_news_block news => OpacHeader %]
                    </div>
                </div>
            </div>
        [% END %]

    </div> <!-- / header-region -->

    [% IF ( OpacPublic ) %]
        <div class="container-fluid">
            [% UNLESS ( advsearch ) %]

            [% END # / UNLESS advsearch %]

        </div> <!-- /.container-fluid -->
    [% END # / OpacPublic %]

    <!-- Login form hidden by default, used for modal window -->
    <div id="loginModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="modalLoginLabel" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h2 class="modal-title" id="modalLoginLabel">Log in to your account</h2>
                    <button type="button" class="closebtn" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">&times;</span>
                    </button>
                </div>
                <form action="/cgi-bin/koha/opac-user.pl" method="post" name="auth" id="modalAuth">
                    <input type="hidden" name="has-search-query" id="has-search-query" value="" />
                    <div class="modal-body">
                        [% IF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
                            <a href="/cgi-bin/koha/svc/auth/googleopenidconnect" class="btn btn-light" id="openid_connect"><i class="fa fa-google" aria-hidden="true"></i> Log in with Google</a>
                            <p>If you do not have a Google account, but do have a local account, you can still log in: </p>
                        [% END # /IF GoogleOpenIDConnect %]
                        [% IF ( shibbolethAuthentication ) %]
                            [% IF ( invalidShibLogin ) %]
                                <!-- This is what is displayed if shibboleth login has failed to match a koha user -->
                                <div class="alert alert-info">
                                    <p>Sorry, your Shibboleth identity does not match a valid library identity. If you have a local login, you may use that below.</p>
                                </div>
                            [% ELSE %]
                                <h3>Shibboleth login</h3>
                                <p><a href="[% shibbolethLoginUrl | $raw %]">Log in using a Shibboleth account</a>.</p>
                                [% UNLESS Koha.Preference('opacShibOnly') %]
                                    <h3>Local login</h3>
                                [% END %]
                            [% END %]
                        [% END %]
                        [% UNLESS Koha.Preference('opacShibOnly') %]
                            <input type="hidden" name="koha_login_context" value="opac" />
                            <fieldset class="brief">
                                <label for="muserid">Login:</label><input type="text" id="muserid" name="userid" autocomplete="off" />
                                <label for="mpassword">Password:</label><input type="password" id="mpassword" name="password" autocomplete="off" />
                                [% IF OpacLoginInstructions %]
                                    <div id="nologininstructions-modal" class="nologininstructions">
                                        [% PROCESS koha_news_block news => OpacLoginInstructions %]
                                    </div>
                                [% END %]
                                [% IF Koha.Preference('OpacPasswordChange') && Categories.can_any_reset_password %]
                                    <div id="forgotpassword-modal" class="forgotpassword">
                                        <a href="/cgi-bin/koha/opac-password-recovery.pl">Forgot your password?</a>
                                    </div>
                                [% END %]
                                [% IF PatronSelfRegistration && PatronSelfRegistrationDefaultCategory %]
                                    <div id="patronregistration-modal" class="patronregistration">
                                        <p>Don't have an account? <a href="/cgi-bin/koha/opac-memberentry.pl">Register here.</a></p>
                                    </div>
                                [% END %]
                            </fieldset>
                        [% END %]
                    </div>
                    [% UNLESS Koha.Preference('opacShibOnly') %]
                        <div class="modal-footer">
                            <input type="submit" class="btn btn-primary" value="Log in" />
                        </div>
                    [% END %]
                </form> <!-- /#auth -->
            </div> <!-- /.modal-content -->
        </div> <!-- /.modal-dialog -->
    </div>  <!-- /#modalAuth  -->
