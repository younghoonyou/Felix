import React from 'react';
import Number from './Number';
const NumberBox = (props) => {
  const { amount, total } = props;
  return (
    <>
      <div className='number-box'>
        <div className='number-small'>
          <Number num={1} amount={amount} total={total} flag={false} />
          <Number num={2} amount={amount} total={total} flag={false} />
          <Number num={3} amount={amount} total={total} flag={false} />
        </div>
        <div className='number-small'>
          <Number num={4} amount={amount} total={total} flag={false} />
          <Number num={5} amount={amount} total={total} flag={false} />
          <Number num={6} amount={amount} total={total} flag={false} />
        </div>
        <div className='number-small'>
          <Number num={7} amount={amount} total={total} flag={false} />
          <Number num={8} amount={amount} total={total} flag={false} />
          <Number num={9} amount={amount} total={total} flag={false} />
        </div>
        <div className='number-small'>
          <Number num={'.'} amount={amount} total={total} flag={false} />
          <Number num={0} amount={amount} total={total} flag={false} />
          <Number
            num={<i className='fa-solid fa-delete-left fa-xs'></i>}
            amount={amount}
            total={total}
            flag={true}
          />
        </div>
      </div>
    </>
  );
};

export default NumberBox;
