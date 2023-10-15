(function( w ){
    // if the class is already set, the font has already been loaded
    if( w.document.documentElement.className.indexOf( "fonts-loaded" ) > -1 ){
        return;
    }
    var PrimaryFont = new w.FontFaceObserver( "NotoSans", {
        weight: 400
    });

    PrimaryFont.load(null, 5000).then(function(){
        w.document.documentElement.className += " fonts-loaded";
    }, function(){
        console.log("Failed");
    });
}( this ));

// http://stackoverflow.com/questions/1038746/equivalent-of-string-format-in-jquery/5341855#5341855
String.prototype.format = function() { return formatstr(this, arguments) }
function formatstr(str, col) {
    col = typeof col === 'object' ? col : Array.prototype.slice.call(arguments, 1);
    var idx = 0;
    return str.replace(/%%|%s|%(\d+)\$s/g, function (m, n) {
        if (m == "%%") { return "%"; }
        if (m == "%s") { return col[idx++]; }
        return col[n];
    });
};

function confirmDelete(message) {
    return (confirm(message) ? true : false);
}

function Dopop(link) {
    newin=window.open(link,'popup','width=500,height=400,toolbar=false,scrollbars=yes,resizable=yes');
}

jQuery.fn.preventDoubleFormSubmit = function() {
    jQuery(this).submit(function() {
        if (this.beenSubmitted)
            return false;
        else
            this.beenSubmitted = true;
    });
};

function prefixOf (s, tok) {
    var index = s.indexOf(tok);
    return s.substring(0, index);
}
function suffixOf (s, tok) {
    var index = s.indexOf(tok);
    return s.substring(index + 1);
}

$("body").on("keypress", ".noEnterSubmit", function(e){
    return checkEnter(e);
});

// http://jennifermadden.com/javascript/stringEnterKeyDetector.html
function checkEnter(e){ //e is event object passed from function invocation
    var characterCode; // literal character code will be stored in this variable
    if(e && e.which){ //if which property of event object is supported (NN4)
        characterCode = e.which; //character code is contained in NN4's which property
    } else {
        characterCode = e.keyCode; //character code is contained in IE's keyCode property
    }
    if( characterCode == 13 //if generated character code is equal to ascii 13 (if enter key)
        && e.target.nodeName == "INPUT"
        && e.target.type != "submit" // Allow enter to submit using the submit button
    ){
        return false;
    } else {
        return true;
    }
}

// Adapted from https://gist.github.com/jnormore/7418776
function confirmModal(message, title, yes_label, no_label, callback) {
    $("#bootstrap-confirm-box-modal").data('confirm-yes', false);
    if($("#bootstrap-confirm-box-modal").length == 0) {
        $("body").append('<div id="bootstrap-confirm-box-modal" tabindex="-1" role="dialog" aria-hidden="true" class="modal">\
            <div class="modal-dialog">\
                <div class="modal-content">\
                    <div class="modal-header" style="min-height:40px;">\
                        <h4 class="modal-title"></h4>\
                        <button type="button" class="closebtn" data-dismiss="modal" aria-label="Close">\
                        <span aria-hidden="true">×</span>\
                    </button>\
                    </div>\
                    <div class="modal-body"><p></p></div>\
                    <div class="modal-footer">\
                        <a href="#" id="bootstrap-confirm-box-modal-submit" class="btn btn-danger"><i class="fa fa-check" aria-hidden="true"></i></a>\
                        <a href="#" id="bootstrap-confirm-box-modal-cancel" data-dismiss="modal" class="btn btn-secondary"><i class="fa fa-remove" aria-hidden="true"></i></a>\
                    </div>\
                </div>\
            </div>\
        </div>');
        $("#bootstrap-confirm-box-modal-submit").on('click', function () {
            $("#bootstrap-confirm-box-modal").data('confirm-yes', true);
            $("#bootstrap-confirm-box-modal").modal('hide');
            return false;
        });
        $("#bootstrap-confirm-box-modal").on('hide.bs.modal', function () {
            if(callback) callback($("#bootstrap-confirm-box-modal").data('confirm-yes'));
        });
    }

    $("#bootstrap-confirm-box-modal .modal-header h4").text( title || "" );
    if( message && message != "" ){
        $("#bootstrap-confirm-box-modal .modal-body").html( message || "" );
    } else {
        $("#bootstrap-confirm-box-modal .modal-body").remove();
    }
    $("#bootstrap-confirm-box-modal-submit").text( yes_label || 'Confirm' );
    $("#bootstrap-confirm-box-modal-cancel").text( no_label || 'Cancel' );
    $("#bootstrap-confirm-box-modal").modal('show');
}

//Add jQuery :focusable selector
(function($) {
    function visible(element) {
        return $.expr.filters.visible(element) && !$(element).parents().addBack().filter(function() {
            return $.css(this, 'visibility') === 'hidden';
        }).length;
    }

    function focusable(element, isTabIndexNotNaN) {
        var map, mapName, img, nodeName = element.nodeName.toLowerCase();
        if ('area' === nodeName) {
            map = element.parentNode;
            mapName = map.name;
            if (!element.href || !mapName || map.nodeName.toLowerCase() !== 'map') {
                return false;
            }
            img = $('img[usemap=#' + mapName + ']')[0];
            return !!img && visible(img);
        }
        return (/input|select|textarea|button|object/.test(nodeName) ?
                !element.disabled :
                'a' === nodeName ?
                element.href || isTabIndexNotNaN :
                isTabIndexNotNaN) &&
            // the element and all of its ancestors must be visible
            visible(element);
    }

    $.extend($.expr[':'], {
        focusable: function(element) {
            return focusable(element, !isNaN($.attr(element, 'tabindex')));
        }
    });
})(jQuery);

$("#scrolltocontent").click(function() {
    var content = $(".maincontent");
    if (content.length > 0) {
        $('html,body').animate({
                scrollTop: content.first().offset().top
            },
        'slow');
        content.first().find(':focusable').eq(0).focus();
    }
});
