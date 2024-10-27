<!DOCTYPE html>

<html lang="zh">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>支付接口demo</title>
    <script type="text/javascript" src="/demo/jquery-1.10.2.js"></script>
    <script type="text/javascript" src="/demo/jquery.qrcode.min.js"></script>
    <style>
        .pay-panel
        {
            width: 640px;
            height: 900px;
            margin: 100px auto 0 auto;
            border: 1px solid #dddddd;
            position: relative;
        }
        .pay-panel .operation-panel
        {
            position: absolute;
            line-height: 40px;
            text-align: center;
            width: 100%;
            bottom: 20px;
        }
       .pay-panel .operation-panel>div
       {
           width: 180px;
           line-height: 40px;
           display: inline-block;
           margin-right: 20px;
           font-size: 24px;
           border: 1px solid;
           cursor: pointer;
           position:relative;
       }

        .pay-panel .operation-panel > div .disabled {
            opacity: 0.7;
        }

        .pay-panel .operation-panel > div:last-child {
            margin-right: 0;
        }
        .pay-panel #qrcode{
            text-align: center
        }
        .pay-panel #qrcode > canvas {
            margin-top: 160px;
        }
    </style>
</head>
<body>
    <div class="pay-panel">
         <div id="qrcode" ></div>
        <div class="operation-panel">
             <div class="create-btn">创建</div>
            <div class="cancel-btn">取消</div>
            <div class="refund-btn">退款</div>
            <div class="chaxun-btn">查询</div>
            <div style="display:block;border: 0;width: 100%;">
                <label>订单号：</label><input  id="order_id"/>
            </div>
        </div>
    </div>
    <script type="text/javascript">
        $(".create-btn").click(function () {
            if ($(this).hasClass("disabled")) {
                alert("客官别点这么快，，慢点哦");
                return;
            }
            var thisDom = $(this).addClass("disabled");
            $("<div>").css({ width: "100px", height: "100px", opacity: "0.2", background: "white", position: "absolute" }).appendTo(thisDom);
            $.ajax({
                type: 'post',
                url: '/demo/order/orderCreate.do',
                async: true,
                data: { action: 'create' },
                success: function (result) {
                    result = JSON.parse(result);
                    if (result && result.ret_content) {
                        if (result.ret_code == "0") {
                            console.log(result.ret_content);
                            $("#qrcode canvas").remove();
                            $("#qrcode").qrcode({
                                render: "canvas", //table方式 
                                width: 500, //宽度 
                                height: 500, //高度 
                                text: result.ret_content.url //任意内容 
                            });
                            $("#order_id").val(result.ret_content.out_trade_no);
                            alert("创建订单成功！");
                        }
                        else {
                            alert(result.ret_content);
                        }
                    }
                    thisDom.removeClass("disabled");
                },
                error: function () {
                    thisDom.removeClass("disabled");
                    alert("创建失败");
                }
            });
        });
        $(".cancel-btn").click(function () {
            if ($("#order_id").val() == "") {
                alert("订单号错误");
                return;
            }
            $.ajax({
                type: 'get',
                url: '/demo/order/orderRemove.do',
                async: true,
                data: { action: 'cancel',order_id:$("#order_id").val() },
                success: function (result) {
                    result = JSON.parse(result);
                    if (result.ret_code == "0") {
                        alert("成功");
                    }
                    else {
                        alert(result.ret_content);
                    }
                },
                error: function () {
                    console.log("error");
                    alert("取消失败");
                }
            });
        });
        $(".refund-btn").click(function () {
            $.ajax({
                type: 'get',
                url: '/demo/order/orderRefund.do',
                async: true,
                data: { action: 'send_notice', order_id: $("#order_id").val() },
                success: function (result) {
                	alert(result);
                },
                error: function () {
                    console.log("error");
                }
            });
        });
        
        $(".chaxun-btn").click(function () {
            if ($("#order_id").val() == "") {
                alert("订单号错误");
                return;
            }
            $.ajax({
                type: 'get',
                url: '/demo/order/selectOrderQuery.do',
                async: true,
                data: { action: 'chaxun',order_id:$("#order_id").val() },
                success: function (result) {
                    result = JSON.parse(result);
                    if (result.ret_code == "0") {
                        alert("成功");
                    }
                    else {
                        alert(result.ret_content);
                    }
                },
                error: function () {
                    console.log(result);
                    alert("查询失败");
                }
            });
        });
    </script>
</body>
</html>