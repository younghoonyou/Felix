import React from 'react';
const Number = (props) => {
  const { num, amount, total, flag } = props;
  const target = flag;
  return (
    <>
      <button
        className='num-button'
        type='button'
        onClick={() => {
          if (target) {
            amount(String(total).slice(0, -1));
          } else {
            amount(String(total) + String(num));
          }
        }}
      >
        {num}
      </button>
    </>
  );
};

export default Number;
