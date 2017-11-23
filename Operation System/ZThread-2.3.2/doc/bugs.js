// Fix for bug in IE6.0 float handling - from plone.org

if (document.all && window.attachEvent) window.attachEvent("onload", fixWinIE);
function fixWinIE() {
    try {
        document.getElementById('content').style.display = 'block';
    } catch(er) {}
}

