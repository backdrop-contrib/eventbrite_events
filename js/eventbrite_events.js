(function ($) {

Backdrop.behaviors.form_validation_scripts_newtypes = {
        attach: function(context) {
            $(document).ready(function() {
try {
    var input = document.createElement("input");
    input.type = "tel";
    if (input.type === "tel") {
    $("#edit-billing-phone").prop('type', 'tel');
    $("#edit-billing-zip").prop('type', 'tel');
    $("#edit-card").prop('type', 'tel');
    $("#edit-cvc").prop('type', 'tel');
    } else {
    }
} catch(e) {
}

// var.replace(/[^0-9]+/g, '');

            });
        }
    };




    Backdrop.behaviors.form_validation_scripts_geobytes = {
        attach: function(context) {
            $(document).ready(function() {

$("#edit-billing-city").autocomplete({
    source: function (request, response) {
     jQuery.getJSON(
      "http://gd.geobytes.com/AutoCompleteCity?callback=?&q="+request.term,
      function (data) {
       $("ul.ui-autocomplete").css("backgroundColor", "#bbb");
       response(data);
      }
     );
    },
    minLength: 3,
    select: function (event, ui) {
     var selectedObj = ui.item.value;
     var addressarray = selectedObj.split(',');
     jQuery("#edit-billing-city").val(addressarray[0]);
     jQuery("#edit-billing-state").val(addressarray[1]);
     jQuery("#edit-billing-country").val(addressarray[2]);
     return false;
    },
    open: function () {
     // jQuery(this).removeClass("ui-corner-all").addClass("ui-corner-top");
    },
    close: function () {
     // jQuery(this).removeClass("ui-corner-top").addClass("ui-corner-all");
    }
   });
   $("#edit-billing-city").autocomplete("option", "delay", 100);

            });
        }
    };


Backdrop.behaviors.form_validation_scripts_jessepollak = {
        attach: function(context) {
            $(document).ready(function() {

$('#edit-payment').append('<input type="hidden" name="expiry" id="expiry" value=""></input>');
$('#edit-payment').append('<input type="hidden" name="name" id="name" value="Andrew Martha"></input>');
$('#edit-month, #edit-year').on('change', function () {
    // Set the value of a hidden input field for Card
    $('#expiry').val($('#edit-month').val() + '/' + $('#edit-year').val());
    // Trigger the "change" event manually
    var evt = document.createEvent('HTMLEvents');
    evt.initEvent('change', false, true);
    document.getElementById('expiry').dispatchEvent(evt);
});


$('#basic-cart-braintree-create-form').card({
    container: '#basic-cart-braintree-create-form',
formSelectors: {
        numberInput: '#edit-card', // optional — default input[name="number"]
        expiryInput: '#expiry', // optional — default input[name="expiry"]
        cvcInput: '#edit-cvc', // optional — default input[name="cvc"]
        nameInput: '#name' // optional - defaults input[name="name"]
    },

    width: 316, // optional — default 350px
    formatting: true, // optional - default true

    // Strings for translation - optional
    messages: {
        validDate: 'valid\ndate', // optional - default 'valid\nthru'
        monthYear: 'mm/yyyy', // optional - default 'month/year'
    },

    // Default placeholders for rendered fields - optional
    placeholders: {
        number: '•••• •••• •••• ••••',
        name: 'Full Name',
        expiry: '••/••',
        cvc: '•••'
    },

    // if true, will log helpful messages for setting up Card
    debug: false // optional - default false


});

var options = $('.form-type-select.form-item-month').children('select').children('option');
for (i = 0; i < options.length; i++)
{
var thetext = options[i].innerText;
thesplit = thetext.split('v');
options[i].innerText = thesplit[0];
}
var options = $('.form-type-select.form-item-year').children('select').children('option');
for (i = 0; i < options.length; i++)
{
var thetext = options[i].innerText;
thesplit = thetext.split('v');
options[i].innerText = thesplit[0];
}

var txt = $("#edit-card");
var func = function() {
    txt.val(txt.val().replace(/\s/g, ''));
  }
txt.keyup(func).blur(func);




            });
        }
    };


Backdrop.behaviors.form_validation_scripts_jquerypayment = {
        attach: function(context) {
            $(document).ready(function() {
$('#edit-card').payment('restrictNumeric');
$('#edit-cvc').payment('restrictNumeric');

var func = function() {
    var isvalid = false;
    var cardnum = document.getElementById('edit-card').value;
    isvalid = $.payment.validateCardNumber(cardnum);
    if (isvalid == true)
    {
    $('#edit-card').css("color", "#000000");
    }
    else
    {
    $('#edit-card').css("color", "#ff0000").focus();
    return false;
    }

  }

$("#edit-card").blur(func);
$('#basic-cart-braintree-create-form').submit(function(event) {
func;

var month = document.getElementById('edit-month').value;
var year = document.getElementById('edit-year').value;
var isvalid = false;
isvalid = $.payment.validateCardExpiry(month, year);
if (isvalid == true)
{
$('#edit-month').css("color", "#000000");
}
else
{
$('#edit-month').css("color", "#ff0000").focus();
return false;
}



});



});
        }
    };


})(jQuery);
