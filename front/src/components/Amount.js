import React from "react";

const Amount = (props) => {
    const { amount, onChange } = props;
    console.log(amount);
    return (
        <>
            <div className="Amount-Box">
                <text className="Amount-sale">
                    Sale amount
                </text>
                <text className="Amount-text" onChange={onChange}>
                    ${amount}
                </text>
            </div>
        </>
    )
}
export default Amount;