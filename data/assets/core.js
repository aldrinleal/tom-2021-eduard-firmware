$(() => {
    $(".command").bind("click", (event) => {
        let direction = event.target.dataset.direction;

        console.log("direction", direction);
        console.log("src", event)

        $.ajax({
            type: 'post',
            dataType: 'json',
            url: '/action',
            data: JSON.stringify({ direction }),
            contentType: "application/json; charset=utf-8",
            traditional: true,
        });
    })
})