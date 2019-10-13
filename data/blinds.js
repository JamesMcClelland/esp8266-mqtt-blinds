$(document).ready(function(){

    function makeRequest(url, args) {
        $.get(url, args, function(data){
            if (data !== 'ok') {
                alert("Response was not 'ok' response was: " , data);
            }
        });
    }

    $('.js-go-to').click(function(){
        let percentage = $(this).data("value");
        makeRequest('goto', {'place' : percentage});
    });

    $('.show-config').click(function(){
        $('.configurator').toggle();
        
        $('.js-rotate').unbind("click");
        $('.js-rotate').click(function(){
            let value = $(this).data("value");
            makeRequest('turn', {'amount' : value});
        });
        
        $('.js-set-percentage').unbind("click");
        $('.js-set-percentage').click(function(){
            let value = $(this).data("value");
            makeRequest('limit', {'amount' : value});
        });
    });

});