import React from "react";
import Number from "./Number";
const NumberBox = (props) => {
    const { amount,total } = props;
    return (
      <>
        <div className='NumberBox'>
          <div className='Numbersmall'>
            <Number num={1} amount={amount} total={total} flag={false} />
            <Number num={2} amount={amount} total={total} flag={false} />
            <Number num={3} amount={amount} total={total} flag={false} />
          </div>
          <div className='Numbersmall'>
            <Number num={4} amount={amount} total={total} flag={false} />
            <Number num={5} amount={amount} total={total} flag={false} />
            <Number num={6} amount={amount} total={total} flag={false} />
          </div>
          <div className='Numbersmall'>
            <Number num={7} amount={amount} total={total} flag={false} />
            <Number num={8} amount={amount} total={total} flag={false} />
            <Number num={9} amount={amount} total={total} flag={false} />
          </div>
          <div className='Numbersmall'>
            <Number num={9} amount={amount} total={total} flag={false} />
            <Number num={0} amount={amount} total={total} flag={false} />
            <Number num={'\u21e6'} amount={amount} total={total} flag={true} />
          </div>
        </div>
      </>
    );
}

export default NumberBox;